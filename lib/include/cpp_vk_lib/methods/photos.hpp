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
class photos : protected document::common {
public:
  std::string get_messages_upload_server    (std::int64_t peer_id) const;
  std::string get_chat_upload_server        (std::int64_t chat_id, std::int64_t crop = 512) const;
  vk::attachment::attachments_t search      (std::string_view query, std::int64_t count) const;
  std::shared_ptr<vk::attachment::photo> save_messages_photo(std::string_view filename, std::string_view raw_server) const;
private:
  method_utils method_util;
};
} // namespace method
} // namespace vk

#endif // VK_PHOTOS_H
