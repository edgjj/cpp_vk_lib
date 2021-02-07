#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include "string_util/implementation/separated_list.hpp"
#include "string_util/implementation/split.hpp"


namespace vk
{
namespace string_util
{
template <typename T>
std::string separated_list(std::initializer_list<T>&& elements, char delimiter)
{
    return separated_list_implementation<T>::create(elements, delimiter, std::is_integral<T>());
}

std::vector<std::string_view> split(std::string_view text, char delimiter) noexcept
{
    return split_implementation::create(text, delimiter);
}
} // namespace string_util
} // namespace vk

#endif // STRING_UTIL_H
