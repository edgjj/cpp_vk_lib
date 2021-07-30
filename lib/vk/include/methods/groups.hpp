#ifndef VK_METHODS_GROUPS_HPP
#define VK_METHODS_GROUPS_HPP

#include "vk/include/methods/utility/constructor.hpp"

#include <memory>

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

    int64_t get_by_id() const;
    simdjson::dom::object get_long_poll_server(int64_t group_id) const;

protected:
    mutable method::group_constructor m_group_constructor;
    std::shared_ptr<simdjson::dom::parser> m_parser;
};

}// namespace method
}// namespace vk

#endif// VK_METHODS_GROUPS_HPP
