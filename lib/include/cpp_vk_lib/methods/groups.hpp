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
class groups
{
public:
    explicit groups()
      : m_method_util()
    {}

    groups(const groups&) = default;
    groups(groups&&) = default;
    groups& operator=(const groups&) = default;
    groups& operator=(groups&&) = default;
    ~groups() = default;

    std::int64_t get_by_id() const;
    simdjson::dom::object get_long_poll_server(std::int64_t group_id) const;

protected:
    method::utility m_method_util;
};
}// namespace method
}// namespace vk

#endif// VK_GROUPS_H
