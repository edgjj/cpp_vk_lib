#ifndef VK_GROUPS_H
#define VK_GROUPS_H

#include "methods/utility/constructor.hpp"

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

    ~groups();

    std::int64_t get_by_id() const;
    simdjson::dom::object get_long_poll_server(std::int64_t group_id) const;

protected:
    mutable method::group_constructor_proxy m_group_constructor;
    std::shared_ptr<simdjson::dom::parser> m_parser;
};
}// namespace method
}// namespace vk

#endif// VK_GROUPS_H
