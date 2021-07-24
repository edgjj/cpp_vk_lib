#include "methods/photos.hpp"

#include "exception/error-inl.hpp"
#include "simdjson.h"

vk::method::photos::photos()
    : m_parser(std::make_shared<simdjson::dom::parser>())
    , m_document() {}

vk::method::photos::photos(std::string_view user_token)
    : m_parser(std::make_shared<simdjson::dom::parser>())
    , m_document(user_token.data()) {}

vk::method::photos::~photos() = default;

vk::attachment::attachments_t vk::method::photos::search(std::string_view query, int64_t count) const
{
    return m_document.search("photos.search", query, count);
}

std::string vk::method::photos::get_messages_upload_server(int64_t peer_id) const
{
    return m_group_constructor
        .method("photos.getMessagesUploadServer")
        .param("peer_id", std::to_string(peer_id))
        .perform_request();
}

std::string vk::method::photos::get_chat_upload_server(int64_t chat_id, int64_t crop) const
{
    return m_group_constructor
        .method("photos.getChatUploadServer")
        .param("crop_x", std::to_string(crop))
        .param("crop_y", std::to_string(crop))
        .param("chat_id", std::to_string(chat_id - vk::method::utility::chat_id_constant))
        .perform_request();
}

static std::map<std::string, std::string> save_messages_photo_args(simdjson::dom::object upload_response)
{
    return {
        {"photo", upload_response["photo"].get_c_str().take_value()},
        {"hash", upload_response["hash"].get_c_str().take_value()},
        {"server", std::to_string(upload_response["server"].get_int64())}};
}

std::shared_ptr<vk::attachment::photo> vk::method::photos::save_messages_photo(std::string_view filename, std::string_view raw_server) const
{
    const simdjson::dom::object response = m_document.upload(filename, raw_server, "file");

    if (response["photo"].get_string().take_value() == "[]" || response["photo"].get_string().take_value().empty()) {
        exception::dispatch_error_by_code(response["error"]["error_code"].get_int64(), exception::log_before_throw);
    }

    const std::string raw_response = m_group_constructor
        .method("photos.saveMessagesPhoto")
        .append_map(save_messages_photo_args(response))
        .perform_request();

    const simdjson::dom::object uploaded = m_parser->parse(raw_response)["response"].at(0);

    const int64_t owner_id = uploaded["owner_id"].get_int64();
    const int64_t id = uploaded["id"].get_int64();

    return std::make_shared<vk::attachment::photo>(owner_id, id);
}
