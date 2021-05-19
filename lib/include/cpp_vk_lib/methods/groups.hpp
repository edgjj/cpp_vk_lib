#ifndef VK_GROUPS_H
#define VK_GROUPS_H

#include "methods/utility/raw_method.hpp"

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
    explicit groups();

    groups(const groups&) = default;
    groups(groups&&) = default;
    groups& operator=(const groups&) = default;
    groups& operator=(groups&&) = default;
    ~groups() = default;

    std::int64_t get_by_id() const;
    simdjson::dom::object get_long_poll_server(std::int64_t group_id) const;

protected:
    mutable method::group_raw_method m_group_raw_method;
    std::shared_ptr<simdjson::dom::parser> m_parser;
};
}// namespace method
}// namespace vk

#endif// VK_GROUPS_H
