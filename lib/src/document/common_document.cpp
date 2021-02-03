#include <simdjson.h>

#include "lib/include/document/common_document.hpp"


template <typename Function>
static void search_attachments(const simdjson::dom::array& items, Function&& function)
{
    for (std::size_t i = 0; i < items.size() && i < 10; i++)
    {
        std::size_t index = rand() % items.size();
        function(index);
    }
}

vk::attachment::attachments_t vk::document::common::common_search(std::string_view type, std::string_view query, std::int64_t count)
{
    vk::attachment::attachments_t documents;
    std::string raw_json = call(type, user_params({{"q", query.data()}, {"count", std::to_string(count)}}));
    simdjson::dom::array items = parser.parse(raw_json)["response"]["items"].get_array();

    if (items.size() == 0) { return documents; }

    if (type == "photos.search") search_attachments(items, [&documents, &items](std::size_t index){
        documents.push_back(std::make_shared<vk::attachment::photo_attachment>(
            static_cast<std::int64_t>(items.at(index)["owner_id"]),
            static_cast<std::int64_t>(items.at(index)["id"])
        ));
    });
    else if (type == "video.search") search_attachments(items, [&documents, &items](std::size_t index){
        documents.push_back(std::make_shared<vk::attachment::video_attachment>(
            static_cast<std::int64_t>(items.at(index)["owner_id"]),
            static_cast<std::int64_t>(items.at(index)["id"])
        ));
    });
    else if (type == "docs.search") search_attachments(items, [&documents, &items](std::size_t index){
        documents.push_back(std::make_shared<vk::attachment::document_attachment>(
            static_cast<std::int64_t>(items.at(index)["owner_id"]),
            static_cast<std::int64_t>(items.at(index)["id"]),
            static_cast<std::string_view>(items.at(index)["url"])
        ));
    });

    return documents;
}

simdjson::dom::object vk::document::common::common_upload(
    simdjson::dom::parser& parser,
    const vk::lib::network_client& network_client,
    std::string_view filename,
    std::string_view server,
    std::string_view field_name)
{
    return
    parser.parse(
        network_client.upload(
            field_name,
            filename,
            static_cast<std::string_view>(parser.parse(server)["response"]["upload_url"])
        )
    );
}
