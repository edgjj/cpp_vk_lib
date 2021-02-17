#ifndef VK_UTILS_H
#define VK_UTILS_H

#include "api/service.hpp"


namespace vk {
/*!
 * @brief The utils methods representation.
 *
 * Please, inherit this class to add new methods.
 */
class vk_export utils : protected service {
public:
  explicit utils(std::string_view user_token_) : service(user_token_) { };
  explicit utils() = default;
  ~utils() = default;

  bool check_link                   (std::string_view url);
  std::string get_short_link        (std::string_view url);
  std::int64_t resolve_screen_name  (std::string_view screen_name);
};
} // namespace vk

#endif // VK_UTILS_H
