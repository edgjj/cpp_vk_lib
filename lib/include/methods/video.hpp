#ifndef VK_VIDEO_H
#define VK_VIDEO_H

#include "document/common_document.hpp"


namespace vk {
/*!
 * @brief The video methods representation.
 *
 * Please, inherit this class to add new methods.
 */
class vk_export video : protected document::common {
public:
  explicit video(std::string_view user_token_) : document::common(user_token_) { }
  explicit video() = default;
  ~video() = default;

  vk::attachment::attachments_t search(std::string_view query, std::int64_t count);
  void save_by_link(std::string_view url);
};
} // namespace vk

#endif // VK_VIDEO_H
