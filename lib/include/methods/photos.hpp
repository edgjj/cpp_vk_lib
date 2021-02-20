#ifndef VK_PHOTOS_H
#define VK_PHOTOS_H

#include "document/common_document.hpp"


namespace vk {
namespace method {
/*!
 * @brief The photos methods representation.
 *
 * Please, inherit this class to add new methods.
 */
class vk_export photos : protected document::common {
public:
  std::string get_messages_upload_server    (std::int64_t peer_id);
  std::string get_chat_upload_server        (std::int64_t chat_id, std::int64_t crop = 512);
  vk::attachment::attachments_t search      (std::string_view query, std::int64_t count);
  std::shared_ptr<vk::attachment::photo_attachment> save_messages_photo(std::string_view filename, std::string_view raw_server);
private:
  method_utils method_util;
  network_client net_client;
};
} // namespace method
} // namespace vk

#endif // VK_PHOTOS_H
