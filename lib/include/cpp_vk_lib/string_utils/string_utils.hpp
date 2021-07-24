#ifndef VK_STRING_UTILS_HPP
#define VK_STRING_UTILS_HPP

#include "string_utils/implementation/convert_ascii.hpp"
#include "string_utils/implementation/convert_utf8.hpp"
#include "string_utils/implementation/format.hpp"
#include "string_utils/implementation/join.hpp"
#include "string_utils/implementation/lazy_split.hpp"
#include "string_utils/implementation/split.hpp"

namespace vk {
namespace string_utils {

template <typename T, typename Container>
std::string join(Container&& elements, char delimiter)
{
    return join_impl<T>::create(std::forward<Container>(elements), delimiter);
}

template <typename T>
std::string join(std::initializer_list<T> elements, char delimiter)
{
    return join_impl<T>::create(elements, delimiter);
}

template <typename... Args>
std::string format(std::string_view data, Args&&... args)
{
    return format_impl<Args...>::create(data, std::forward<Args>(args)...);
}

inline std::vector<std::string_view> split(std::string_view data, char delimiter)
{
    return split_impl::create(data, delimiter);
}

inline auto lazy_split(std::string_view data, std::string_view delimiter)
{
    return split_range<std::string_view>(data, delimiter);
}

inline std::string utf8_to_lower(std::string_view data)
{
    return utf8_convert_impl::create_lower(data);
}

inline std::string utf8_to_upper(std::string_view data)
{
    return utf8_convert_impl::create_upper(data);
}

inline std::string ascii_to_lower(std::string_view data)
{
    return ascii_convert_impl::create_lower(data);
}

inline std::string ascii_to_upper(std::string_view data)
{
    return ascii_convert_impl::create_upper(data);
}

}// namespace string_utils
}// namespace vk

#endif// VK_STRING_UTILS_HPP
