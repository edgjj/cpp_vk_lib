#include "vk/include/document/common.hpp"

#include "runtime/include/net/network.hpp"

#include "simdjson.h"

#include <random>

vk::document::common::common()
    : m_parser(std::make_shared<simdjson::dom::parser>()) {}

vk::document::common::common(std::string_view user_token)
    : m_parser(std::make_shared<simdjson::dom::parser>())
    , m_group_constructor(user_token.data()) {}

vk::document::common::~common() = default;

template <typename ExecutionPolicy>
static void search_attachments(int32_t items_size, ExecutionPolicy&& adding_policy)
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(1, items_size);

    for (uint8_t i = 0; i < items_size && i < 10; i++) {
        const size_t index = distribution(generator);
        adding_policy(index);
    }
}

std::vector<vk::attachment::attachment_ptr_t> vk::document::common::search(std::string_view method, std::string_view query, int64_t count) const
{
    std::vector<vk::attachment::attachment_ptr_t> documents;

    const std::string raw_response = m_group_constructor
        .method(method)
        .param("q", query)
        .param("count", std::to_string(count))
        .perform_request();

    const simdjson::dom::array items = m_parser->parse(raw_response)["response"]["items"].get_array();
    documents.reserve(items.size());

    if (items.size() == 0) { return {}; }

    if (method == "photos.search") {
        search_attachments(static_cast<int32_t>(items.size()), [&documents, &items](size_t index) {
            documents.push_back(std::make_shared<vk::attachment::photo>(
                items.at(index)["owner_id"].get_int64(),
                items.at(index)["id"].get_int64()));
        });
    } else if (method == "video.search") {
        search_attachments(static_cast<int32_t>(items.size()), [&documents, &items](size_t index) {
            documents.push_back(std::make_shared<vk::attachment::video>(
                items.at(index)["owner_id"].get_int64(),
                items.at(index)["id"].get_int64()));
        });
    } else if (method == "docs.search") {
        search_attachments(static_cast<int32_t>(items.size()), [&documents, &items](size_t index) {
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
    const std::string upload_server = m_parser->parse(server)["response"]["upload_url"].get_c_str().take_value();
    const std::string upload_response = runtime::network::upload(field_name, filename, upload_server);

    return m_parser->parse(upload_response);
}
