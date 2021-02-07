#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include "string_util/implementation/join.hpp"
#include "string_util/implementation/split.hpp"


namespace vk
{
namespace string_util
{
template <typename T>
std::string join(std::initializer_list<T>&& elements, char delimiter)
{
    return join_implementation<T>::create(elements, delimiter, std::is_integral<T>());
}

std::vector<std::string_view> split(std::string_view text, char delimiter) noexcept
{
    return split_implementation::create(text, delimiter);
}
} // namespace string_util
} // namespace vk

#endif // STRING_UTIL_H
