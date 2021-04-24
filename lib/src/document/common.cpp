#include "document/common.hpp"

#include "simdjson.h"

#include <random>

vk::document::common::common()
  : m_parser(std::make_shared<simdjson::dom::parser>())
  , m_method_util()
  , m_net_client()
{}

vk::document::common::common(std::string_view user_token)
  : m_parser(std::make_shared<simdjson::dom::parser>())
  , m_method_util(user_token.data())
  , m_net_client()
{}

vk::document::common::~common() = default;

template <typename _Execution_Policy>
static void search_attachments(const simdjson::dom::array& items, _Execution_Policy&& policy)
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(1, items.size());

    for (std::size_t i = 0, size = items.size(); i < size && i < 10; i++)
    {
        std::size_t index = distribution(generator);
        policy(index);
    }
}

vk::attachment::attachments_t vk::document::common::search(std::string_view method, std::string_view query, std::int64_t count) const
{
    vk::attachment::attachments_t documents;
    std::string raw_json = m_method_util.call(method, m_method_util.user_args({{"q", query.data()}, {"count", std::to_string(count)}}));
    simdjson::dom::array items = m_parser->parse(raw_json)["response"]["items"].get_array();
    documents.reserve(items.size());

    if (items.size() == 0)
    {
        return documents;
    }

    if (method == "photos.search")
    {
        search_attachments(items, [&documents, &items](std::size_t index) {
            documents.push_back(
                std::make_shared<vk::attachment::photo>(items.at(index)["owner_id"].get_int64(), items.at(index)["id"].get_int64()));
        });
    }
    else if (method == "video.search")
    {
        search_attachments(items, [&documents, &items](std::size_t index) {
            documents.push_back(
                std::make_shared<vk::attachment::video>(items.at(index)["owner_id"].get_int64(), items.at(index)["id"].get_int64()));
        });
    }
    else if (method == "docs.search")
    {
        search_attachments(items, [&documents, &items](std::size_t index) {
            documents.push_back(std::make_shared<vk::attachment::document>(
                items.at(index)["owner_id"].get_int64(),
                items.at(index)["id"].get_int64(),
                items.at(index)["url"].get_string()));
        });
    }

    return documents;
}

simdjson::dom::object vk::document::common::upload(std::string_view filename, std::string_view server, std::string_view field_name) const
{
    return m_parser->parse(m_net_client.upload(field_name, filename, m_parser->parse(server)["response"]["upload_url"].get_string()));
}
