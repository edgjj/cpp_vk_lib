#include "vk/include/methods/audio.hpp"

#include "vk/include/exception/error-inl.hpp"

#include "simdjson.h"

vk::method::audio::audio(vk::error_code& errc)
    : m_stored_error(errc)
    , m_parser(std::make_shared<simdjson::dom::parser>())
    , m_document()
    , m_group_constructor()
    , m_user_constructor() {}

vk::method::audio::audio(vk::error_code& errc, std::string_view user_token)
    : m_stored_error(errc)
    , m_parser(std::make_shared<simdjson::dom::parser>())
    , m_document(user_token.data())
    , m_group_constructor()
    , m_user_constructor(user_token) {}

vk::method::audio::~audio() = default;

std::string vk::method::audio::get_upload_server() const
{
    return m_user_constructor.method("audio.getUploadServer").perform_request();
}

void vk::method::audio::save(std::string_view artist, std::string_view title, std::string_view filename, std::string_view raw_server) const
{
    const simdjson::dom::object response = m_document.upload(filename, raw_server, "file");

    if (response.begin().key() == "error") {
        m_stored_error.assign(exception::translate_error(response["error"]["error_code"].get_int64()));
        return;
    }

    m_group_constructor
        .method("audio.save")
        .param("server", std::to_string(response["server"].get_int64()))
        .param("audio", std::string(response["audio"].get_c_str()))
        .param("hash", std::string(response["hash"].get_c_str()))
        .param("artist", artist)
        .param("title", title)
        .perform_request();
}
