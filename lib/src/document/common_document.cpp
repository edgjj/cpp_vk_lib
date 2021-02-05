#include "document/common_document.hpp"


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
            items.at(index)["owner_id"].get_int64(),
            items.at(index)["id"].get_int64()
        ));
    });
    else if (type == "video.search") search_attachments(items, [&documents, &items](std::size_t index){
        documents.push_back(std::make_shared<vk::attachment::video_attachment>(
            items.at(index)["owner_id"].get_int64(),
            items.at(index)["id"].get_int64()
        ));
    });
    else if (type == "docs.search") search_attachments(items, [&documents, &items](std::size_t index){
        documents.push_back(std::make_shared<vk::attachment::document_attachment>(
            items.at(index)["owner_id"].get_int64(),
            items.at(index)["id"].get_int64(),
            items.at(index)["url"].get_string()
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
            parser.parse(server)["response"]["upload_url"].get_string()
        )
    );
}
