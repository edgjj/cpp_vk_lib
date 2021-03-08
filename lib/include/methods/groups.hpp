#ifndef VK_GROUPS_H
#define VK_GROUPS_H

#include "method_utils/method_utils.hpp"


namespace vk {
namespace method {
/*!
 * @brief The groups methods representation.
 *
 * Please, inherit this class to add new methods.
 */
class groups {
public:
  std::int64_t get_by_id() const;
  simdjson::dom::object get_long_poll_server(std::int64_t group_id) const;
private:
  method_utils method_util;
};
} // namespace method
} // namespace vk

#endif // VK_GROUPS_H
