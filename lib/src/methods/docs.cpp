#include "simdjson.h"

#include "string_util/string_util.hpp"
#include "processing/exception.hpp"
#include "methods/docs.hpp"


vk::attachment::attachments_t vk::docs::search(std::string_view query, std::int64_t count) {
    return common_search("docs.search", query, count);
}

void vk::docs::edit(int64_t owner_id, int64_t doc_id, std::string_view title, std::initializer_list<std::string>&& tags) {
    simdjson::dom::object response =
    call_and_parse("docs.edit", user_args({
        {"owner_id",    std::to_string(owner_id)},
        {"doc_id",      std::to_string(doc_id)},
        {"title",       title.data()},
        {"tags",        string_util::join(std::move(tags)).data()}
    }));

    if (error_returned(response, 1150))
        vk_throw(exception::invalid_parameter_error, 1150, "Invalid document id.");

    if (error_returned(response, 1152))
        vk_throw(exception::invalid_parameter_error, 1152, "Invalid document title.");

    if (error_returned(response, 1153))
        vk_throw(exception::access_error, 1153, "Access to document restricted.");
}

void vk::docs::remove(int64_t owner_id, int64_t doc_id) {
    simdjson::dom::object response =
    call_and_parse("docs.delete", user_args({
        {"owner_id", std::to_string(owner_id)},
        {"doc_id", std::to_string(doc_id)}
    }));

    if (error_returned(response, 1150))
        vk_throw(exception::invalid_parameter_error, 1150, "Invalid document id.");

    if (error_returned(response, 1151))
        vk_throw(exception::invalid_parameter_error, 1151, "Access to document restricted.");
}

std::string vk::docs::get_upload_server(std::int64_t group_id) const {
    return call("docs.getUploadServer", group_args({
        {"group_id", std::to_string(group_id)}
    }));
}

std::string vk::docs::get_wall_upload_server(int64_t group_id) const {
    return call("docs.getWallUploadServer", group_args({
        {"group_id", std::to_string(group_id)}
    }));
}

std::string vk::docs::get_messages_upload_server(std::string_view type, int64_t peer_id) const {
    return call("docs.getMessagesUploadServer", group_args({
        {"peer_id", std::to_string(peer_id)},
        {"type", type.data()}
    }));
}

std::shared_ptr<vk::attachment::audio_message_attachment> vk::docs::save_audio_message(std::string_view filename, std::string_view raw_server) {
    simdjson::dom::object upload_response(common_upload(parser, net_client, filename, raw_server, "file"));
    if (upload_response.begin().key() != "file")
        vk_throw(exception::upload_error, -1, "Can't upload file. Maybe is not an mp3 track?");

    std::string file(upload_response["file"].get_c_str());
    if (file == "") { return { }; }
    std::string raw_save_response(call("docs.save", group_args({{"file", file}, {"title", "voice"}})));
    simdjson::dom::object uploaded_doc(parser.parse(raw_save_response)["response"]["audio_message"]);

    return
    std::make_shared<vk::attachment::audio_message_attachment>(
        uploaded_doc["owner_id"].get_int64(),
        uploaded_doc["id"].get_int64(),
        uploaded_doc["link_ogg"].get_string(),
        uploaded_doc["link_mp3"].get_string()
    );
}
