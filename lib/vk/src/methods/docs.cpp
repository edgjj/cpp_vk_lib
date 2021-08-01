#include "vk/include/methods/docs.hpp"

#include "vk/include/exception/error-inl.hpp"

#include "runtime/include/string_utils/string_utils.hpp"

#include "simdjson.h"

vk::method::docs::docs(error_code& errc)
    : m_stored_error(errc)
    , m_parser(std::make_shared<simdjson::dom::parser>())
    , m_group_constructor()
    , m_user_constructor()
    , m_document() {}

vk::method::docs::docs(error_code& errc, std::string_view user_token)
    : m_stored_error(errc)
    , m_parser(std::make_shared<simdjson::dom::parser>())
    , m_group_constructor()
    , m_user_constructor(user_token.data())
    , m_document(user_token.data()) {}

vk::method::docs::~docs() = default;

vk::attachment::attachments_t vk::method::docs::search(std::string_view query, int64_t count) const
{
    return m_document.search("docs.search", query, count);
}

void vk::method::docs::edit(int64_t owner_id, int64_t doc_id, std::string_view title, std::initializer_list<std::string> tags) const
{
    const std::string raw_response = m_user_constructor
        .method("docs.edit")
        .param("owner_id", std::to_string(owner_id))
        .param("doc_id", std::to_string(doc_id))
        .param("title", title.data())
        .param("tags", runtime::string_utils::join<std::string>(tags).data())
        .perform_request();

    const simdjson::dom::object response = m_parser->parse(raw_response);

    if (response.begin().key() == "error") {
        m_stored_error.assign(exception::translate_error(response["error"]["error_code"].get_int64()));
        return;
    }
}

void vk::method::docs::remove(int64_t owner_id, int64_t doc_id) const
{
    const std::string raw_response = m_user_constructor
        .method("docs.delete")
        .param("owner_id", std::to_string(owner_id))
        .param("doc_id", std::to_string(doc_id))
        .perform_request();

    const simdjson::dom::object response = m_parser->parse(raw_response);

    if (response.begin().key() == "error") {
        m_stored_error.assign(exception::translate_error(response["error"]["error_code"].get_int64()));
        return;
    }
}

std::string vk::method::docs::get_upload_server(int64_t group_id) const
{
    return m_group_constructor
        .method("docs.getUploadServer")
        .param("group_id", std::to_string(group_id))
        .perform_request();
}

std::string vk::method::docs::get_wall_upload_server(int64_t group_id) const
{
    return m_group_constructor
        .method("docs.getWallUploadServer")
        .param("group_id", std::to_string(group_id))
        .perform_request();
}

std::string vk::method::docs::get_messages_upload_server(std::string_view type, int64_t peer_id) const
{
    return m_group_constructor
        .method("docs.getMessagesUploadServer")
        .param("peer_id", std::to_string(peer_id))
        .param("type", type.data())
        .perform_request();
}

std::shared_ptr<vk::attachment::audio_message> vk::method::docs::save_audio_message(std::string_view filename, std::string_view raw_server) const
{
    const simdjson::dom::object upload_response = m_document.upload(filename, raw_server, "file");

    if (upload_response.begin().key() != "file") {
        m_stored_error.assign("Can't upload file. Maybe is not an mp3 track?");
        return {};
    }

    const std::string file = upload_response["file"].get_c_str().take_value();

    if (file.empty()) { return {}; }

    const std::string raw_save_response = m_group_constructor
        .method("docs.save")
        .param("file", file)
        .param("title", "voice")
        .perform_request();

    const simdjson::dom::object uploaded_doc = m_parser->parse(raw_save_response)["response"]["audio_message"];

    return std::make_shared<vk::attachment::audio_message>(
        uploaded_doc["owner_id"].get_int64(),
        uploaded_doc["id"].get_int64(),
        uploaded_doc["link_ogg"].get_string(),
        uploaded_doc["link_mp3"].get_string());
}
