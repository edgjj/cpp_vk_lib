#ifndef VK_UTILS_H
#define VK_UTILS_H

#include "method_utils/method_utils.hpp"


namespace vk {
namespace method {
/*!
 * @brief The utils methods representation.
 *
 * Please, inherit this class to add new methods.
 */
class vk_export utils {
public:
  bool check_link                   (std::string_view url) const;
  std::string get_short_link        (std::string_view url) const;
  std::int64_t resolve_screen_name  (std::string_view screen_name) const;
private:
  method_utils method_util;
};
} // namespace method
} // namespace vk

#endif // VK_UTILS_H
