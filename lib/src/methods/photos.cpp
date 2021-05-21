#include "methods/photos.hpp"

#include "exception/error_processor.hpp"
#include "simdjson.h"

vk::method::photos::photos()
  : m_parser(std::make_shared<simdjson::dom::parser>())
  , m_group_constructor()
  , m_document()
{}

vk::method::photos::photos(std::string_view user_token)
  : m_parser(std::make_shared<simdjson::dom::parser>())
  , m_group_constructor()
  , m_document(user_token.data())
{}

vk::method::photos::~photos() = default;

vk::attachment::attachments_t vk::method::photos::search(std::string_view query, std::int64_t count) const
{
    return m_document.search("photos.search", query, count);
}

std::string vk::method::photos::get_messages_upload_server(std::int64_t peer_id) const
{
    return m_group_constructor
        .method("photos.getMessagesUploadServer")
        .param("peer_id", std::to_string(peer_id))
        .execute();
}

std::string vk::method::photos::get_chat_upload_server(std::int64_t chat_id, std::int64_t crop) const
{
    return m_group_constructor
        .method("photos.getChatUploadServer")
        .param("crop_x", std::to_string(crop))
        .param("crop_y", std::to_string(crop))
        .param("chat_id", std::to_string(chat_id - vk::method::utility::chat_id_constant))
        .execute();
}

static std::map<std::string, std::string> save_messages_photo_args(simdjson::dom::object&& upload_response)
{
    return {
        {"photo", upload_response["photo"].get_c_str().take_value()},
        {"hash", upload_response["hash"].get_c_str().take_value()},
        {"server", std::to_string(upload_response["server"].get_int64())}};
}

std::shared_ptr<vk::attachment::photo> vk::method::photos::save_messages_photo(std::string_view filename, std::string_view raw_server) const
{
    simdjson::dom::object upload_response = m_document.upload(filename, raw_server, "file");

    if (upload_response["photo"].get_string().take_value() == "[]" || upload_response["photo"].get_string().take_value() == "")
    {
        processing::log_and_throw<exception::upload_error>("photos", upload_response);
    }

    std::string raw_response = m_group_constructor
        .method("photos.saveMessagesPhoto")
        .append_map(save_messages_photo_args(std::move(upload_response)))
        .execute();

    simdjson::dom::object uploaded = m_parser->parse(raw_response)["response"].at(0);

    std::int64_t owner_id = uploaded["owner_id"].get_int64();
    std::int64_t id = uploaded["id"].get_int64();

    return std::make_shared<vk::attachment::photo>(owner_id, id);
}
