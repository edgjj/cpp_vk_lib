#ifndef VK_VIDEO_H
#define VK_VIDEO_H

#include "document/common_document.hpp"


namespace vk {
namespace method {
/*!
 * @brief The video methods representation.
 *
 * Please, inherit this class to add new methods.
 */
class vk_export video : protected document::common {
public:
  vk::attachment::attachments_t search(std::string_view query, std::int64_t count) const;
  void save_by_link(std::string_view url) const;
};
} // namespace method
} // namespace vk

#endif // VK_VIDEO_H
