#ifndef VK_METHODS_PHOTOS_HPP
#define VK_METHODS_PHOTOS_HPP

#include "document/common.hpp"
#include "methods/utility/constructor.hpp"

namespace vk {
namespace method {
/*!
 * @brief The photos methods representation.
 *
 * Please, inherit this class to add new methods.
 */
class photos
{
public:
    explicit photos();
    explicit photos(std::string_view user_token);
    ~photos();

    std::string get_messages_upload_server(int64_t peer_id) const;
    std::string get_chat_upload_server(int64_t chat_id, int64_t crop = 512) const;
    vk::attachment::attachments_t search(std::string_view query, int64_t count) const;
    std::shared_ptr<vk::attachment::photo> save_messages_photo(std::string_view filename, std::string_view raw_server) const;

protected:
    std::shared_ptr<simdjson::dom::parser> m_parser;
    mutable method::group_constructor m_group_constructor{};
    mutable method::user_constructor m_user_constructor{};
    document::common m_document;
};

}// namespace method
}// namespace vk

#endif// VK_METHODS_PHOTOS_HPP
