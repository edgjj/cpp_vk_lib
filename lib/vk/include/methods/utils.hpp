#ifndef VK_METHODS_UTILS_HPP
#define VK_METHODS_UTILS_HPP

#include "vk/include/exception/error_code.hpp"
#include "vk/include/methods/utility/constructor.hpp"

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
    utils(error_code& errc);
    ~utils();

    bool check_link(std::string_view url) const;
    std::string get_short_link(std::string_view url) const;
    int64_t resolve_screen_name(std::string_view screen_name) const;

protected:
    error_code& m_stored_error;
    std::shared_ptr<simdjson::dom::parser> m_parser;
    mutable method::group_constructor m_group_constructor;
};

}// namespace method
}// namespace vk

#endif// VK_METHODS_UTILS_HPP
