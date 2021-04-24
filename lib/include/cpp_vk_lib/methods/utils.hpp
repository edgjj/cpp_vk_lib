#ifndef VK_UTILS_H
#define VK_UTILS_H

#include "methods/utility/utility.hpp"

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
    utils(const utils&) = default;
    utils(utils&&) = default;
    utils& operator=(const utils&) = default;
    utils& operator=(utils&&) = default;
    ~utils() = default;

    bool check_link(std::string_view url) const;
    std::string get_short_link(std::string_view url) const;
    std::int64_t resolve_screen_name(std::string_view screen_name) const;

protected:
    method::utility m_method_util;
};
}// namespace method
}// namespace vk

#endif// VK_UTILS_H
