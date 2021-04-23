#ifndef VK_PHOTOS_H
#define VK_PHOTOS_H

#include "document/common.hpp"

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

    photos(const photos&) = default;
    photos(photos&&) = default;
    photos& operator=(const photos&) = default;
    photos& operator=(photos&&) = default;
    ~photos();

    std::string get_messages_upload_server(std::int64_t peer_id) const;
    std::string get_chat_upload_server(std::int64_t chat_id, std::int64_t crop = 512) const;
    vk::attachment::attachments_t search(std::string_view query, std::int64_t count) const;
    std::shared_ptr<vk::attachment::photo> save_messages_photo(std::string_view filename, std::string_view raw_server) const;

protected:
    std::shared_ptr<simdjson::dom::parser> parser;
    method::utility method_util;
    document::common document;
};
}// namespace method
}// namespace vk

#endif// VK_PHOTOS_H
