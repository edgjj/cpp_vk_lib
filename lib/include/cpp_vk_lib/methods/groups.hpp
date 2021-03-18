#ifndef VK_GROUPS_H
#define VK_GROUPS_H

#include "methods/utility/utility.hpp"


namespace vk {
namespace method {
/*!
 * @brief The groups methods representation.
 *
 * Please, inherit this class to add new methods.
 */
class groups {
public:
  explicit groups() : method_util() { }
  std::int64_t get_by_id() const;
  simdjson::dom::object get_long_poll_server(std::int64_t group_id) const;

protected:
  method::utility method_util;
};
} // namespace method
} // namespace vk

#endif // VK_GROUPS_H
