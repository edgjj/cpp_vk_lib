#ifndef VK_UTILS_H
#define VK_UTILS_H

#include "methods/utility/constructor.hpp"

namespace vk {
namespace method {
/*!
 * @brief The utils methods representation.
 *
 * Please, inherit this class to add new methods.
 */
class utils
{
public:
    utils();
    utils(const utils&) = default;
    utils(utils&&) = default;
    utils& operator=(const utils&) = default;
    utils& operator=(utils&&) = default;
    ~utils() = default;

    bool check_link(std::string_view url) const;
    std::string get_short_link(std::string_view url) const;
    std::int64_t resolve_screen_name(std::string_view screen_name) const;

protected:
    std::shared_ptr<simdjson::dom::parser> m_parser;
    mutable method::group_constructor_proxy m_group_constructor;
};
}// namespace method
}// namespace vk

#endif// VK_UTILS_H
