#ifndef RUNTIME_STRING_UTILS_HPP
#define RUNTIME_STRING_UTILS_HPP

#include "runtime/include/string_utils/implementation/convert_ascii.hpp"
#include "runtime/include/string_utils/implementation/convert_utf8.hpp"
#include "runtime/include/string_utils/implementation/format.hpp"
#include "runtime/include/string_utils/implementation/join.hpp"
#include "runtime/include/string_utils/implementation/lazy_split.hpp"
#include "runtime/include/string_utils/implementation/split.hpp"

#include "runtime/include/misc/cppdefs.hpp"

namespace runtime::string_utils {

template <typename T, typename Container>
VK_REALLY_INLINE std::string join(Container&& elements, char delimiter) { return implementation::join<T>(std::forward<Container>(elements), delimiter); }

template <typename T>
VK_REALLY_INLINE std::string join(std::initializer_list<T> elements, char delimiter) { return implementation::join<T>(elements, delimiter); }

template <typename... Args>
VK_REALLY_INLINE std::string format(std::string_view data, Args&&... args) { return implementation::format(data, std::forward<Args>(args)...); }

VK_REALLY_INLINE std::vector<std::string_view> split(std::string_view data, char delimiter) { return implementation::split_implementation(data, delimiter); }
VK_REALLY_INLINE std::vector<std::string_view> whitespace_split(std::string_view data) { return implementation::split_implementation(data, " \f\n\r\t\v"); }
VK_REALLY_INLINE split_range<std::string_view> lazy_split(std::string_view data, std::string_view delimiter) { return split_range<std::string_view>(data, delimiter); }

VK_REALLY_INLINE std::string utf8_to_lower(std::string_view data) { return implementation::create_utf8_lower(data); }
VK_REALLY_INLINE std::string utf8_to_upper(std::string_view data) { return implementation::create_utf8_upper(data); }
VK_REALLY_INLINE std::string ascii_to_lower(std::string_view data) { return implementation::create_ascii_lower(data); }
VK_REALLY_INLINE std::string ascii_to_upper(std::string_view data) { return implementation::create_ascii_upper(data); }

}// namespace runtime::string_utils

#endif// RUNTIME_STRING_UTILS_HPP
