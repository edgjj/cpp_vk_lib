#include "vk/include/methods/video.hpp"

vk::method::video::video(error_code& errc)
    : m_stored_error(errc)
    , m_user_constructor()
    , m_document() {}

vk::method::video::video(error_code& errc, std::string_view user_token)
    : m_stored_error(errc)
    , m_user_constructor(user_token.data())
    , m_document(user_token.data()) {}

vk::method::video::~video() = default;

vk::attachment::attachments_t vk::method::video::search(std::string_view query, int64_t count) const
{
    return m_document.search("video.search", query, count);
}

void vk::method::video::save_by_link(std::string_view url) const
{
    m_user_constructor
        .method("video.save")
        .param("link", url)
        .perform_request();
}
