#include "processing/exception.hpp"
#include "methods/photos.hpp"


vk::attachment::attachments_t vk::photos::search(std::string_view query, std::int64_t count)
{
    return common_search("photos.search", query, count);
}

std::string vk::photos::get_messages_upload_server(std::int64_t peer_id)
{
    return call("photos.getMessagesUploadServer", group_params({
        {"peer_id", std::to_string(peer_id)}
    }));
}

std::string vk::photos::get_chat_upload_server(std::int64_t chat_id)
{
    return call("photos.getChatUploadServer", group_params({
        {"crop_x",     "512"},
        {"crop_y",     "512"},
        {"chat_id",    std::to_string(chat_id - chat_id_constant)}
    }));
}

std::shared_ptr<vk::attachment::photo_attachment> vk::photos::save_messages_photo(std::string_view filename, std::string_view raw_server)
{
    simdjson::dom::object upload_response(common_upload(parser, net_client, filename, raw_server, "file"));

    if (upload_response["photo"].get_string().take_value() == "[]" ||
        upload_response["photo"].get_string().take_value() == "")
    {
        VK_THROW(exception::upload_error, -1, "Can't upload file. Maybe is not an image?");
    }

    std::string raw_vk_response(
        call("photos.saveMessagesPhoto", group_params({
            {"photo",   upload_response["photo"].get_c_str().take_value()},
            {"hash",    upload_response["hash"].get_c_str().take_value()},
            {"server",  std::to_string(upload_response["server"].get_int64())}
        }))
    );

    simdjson::dom::object uploaded_attachment(parser.parse(raw_vk_response)["response"].at(0));

    std::int64_t owner_id(uploaded_attachment["owner_id"].get_int64());
    std::int64_t id(uploaded_attachment["id"].get_int64());

    return std::make_shared<vk::attachment::photo_attachment>(owner_id, id);
}
