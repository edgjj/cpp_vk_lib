#include "methods/docs.hpp"

#include "exception/error_processor.hpp"
#include "simdjson.h"
#include "string_utils/string_utils.hpp"

vk::method::docs::docs()
  : m_parser(std::make_shared<simdjson::dom::parser>())
  , m_group_raw_method()
  , m_user_raw_method()
  , m_document()
{}

vk::method::docs::docs(std::string_view user_token)
  : m_parser(std::make_shared<simdjson::dom::parser>())
  , m_group_raw_method()
  , m_user_raw_method(user_token.data())
  , m_document(user_token.data())
{}

vk::method::docs::~docs() = default;

vk::attachment::attachments_t vk::method::docs::search(std::string_view query, std::int64_t count) const
{
    return m_document.search("docs.search", query, count);
}

void vk::method::docs::edit(int64_t owner_id, int64_t doc_id, std::string_view title, std::initializer_list<std::string>&& tags) const
{
    std::string raw_response = m_user_raw_method.impl()
        .method("docs.edit")
        .param("owner_id", std::to_string(owner_id))
        .param("doc_id", std::to_string(doc_id))
        .param("title", title.data())
        .param("tags", string_utils::join<std::string>(std::move(tags)).data())
        .execute();

    simdjson::dom::object response = m_parser->parse(raw_response);

    if (response.begin().key() == "error")
    {
        processing::log_and_throw<exception::access_error>("messages", response);
    }
}

void vk::method::docs::remove(int64_t owner_id, int64_t doc_id) const
{
    std::string raw_response = m_user_raw_method.impl()
        .method("docs.delete")
        .param("owner_id", std::to_string(owner_id))
        .param("doc_id", std::to_string(doc_id))
        .execute();

    simdjson::dom::object response = m_parser->parse(raw_response);

    if (response.begin().key() == "error")
    {
        processing::log_and_throw<exception::access_error>("messages", response);
    }
}

std::string vk::method::docs::get_upload_server(std::int64_t group_id) const
{
    return m_group_raw_method.impl()
        .method("docs.getUploadServer")
        .param("group_id", std::to_string(group_id))
        .execute();
}

std::string vk::method::docs::get_wall_upload_server(int64_t group_id) const
{
    return m_group_raw_method.impl()
        .method("docs.getWallUploadServer")
        .param("group_id", std::to_string(group_id))
        .execute();
}

std::string vk::method::docs::get_messages_upload_server(std::string_view type, int64_t peer_id) const
{
    return m_group_raw_method.impl()
        .method("docs.getMessagesUploadServer")
        .param("peer_id", std::to_string(peer_id))
        .param("type", type.data())
        .execute();
}

std::shared_ptr<vk::attachment::audio_message>
vk::method::docs::save_audio_message(std::string_view filename, std::string_view raw_server) const
{
    simdjson::dom::object upload_response = m_document.upload(filename, raw_server, "file");

    if (upload_response.begin().key() != "file")
    {
        processing::log_and_throw<exception::upload_error>("docs", "Can't upload file. Maybe is not an mp3 track?");
    }

    std::string file(upload_response["file"].get_c_str());

    if (file == "")
    {
        return {};
    }

    std::string raw_save_response = m_group_raw_method.impl()
        .method("docs.save")
        .param("file", file)
        .param("title", "voice")
        .execute();

    simdjson::dom::object uploaded_doc = m_parser->parse(raw_save_response)["response"]["audio_message"];

    return std::make_shared<vk::attachment::audio_message>(
        uploaded_doc["owner_id"].get_int64(),
        uploaded_doc["id"].get_int64(),
        uploaded_doc["link_ogg"].get_string(),
        uploaded_doc["link_mp3"].get_string());
}
