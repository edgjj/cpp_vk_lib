#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include "misc/cppdefs.hpp"
#include "string_utils/implementation/convert_ascii.hpp"
#include "string_utils/implementation/convert_utf8.hpp"
#include "string_utils/implementation/format.hpp"
#include "string_utils/implementation/join.hpp"
#include "string_utils/implementation/lazy_split.hpp"
#include "string_utils/implementation/split.hpp"

namespace vk {
namespace string_utils {

template <typename T, typename _Container>
std::string join(_Container&& elements, char delimiter) {
  return join_impl<T>::create(std::forward<_Container>(elements), delimiter);
}
template <typename T>
std::string join(std::initializer_list<T> elements, char delimiter) {
  return join_impl<T>::create(elements, delimiter);
}

template <typename... _Args>
std::string format(std::string_view data, _Args&&... args) {
  return format_impl<_Args...>::create(data, std::forward<_Args>(args)...);
}

inline std::vector<std::string_view> split(std::string_view data, char delimiter) {
  return split_impl::create(data, delimiter);
}
inline auto lazy_split(std::string_view data, std::string_view delimiter) {
  return split_range<std::string_view>(data, delimiter);
}

inline std::string utf8_to_lower(std::string_view data) {
  return utf8_convert_impl::create_lower(data);
}
inline std::string utf8_to_upper(std::string_view data) {
  return utf8_convert_impl::create_upper(data);
}
inline std::string ascii_to_lower(std::string_view data) {
  return ascii_convert_impl::create_lower(data);
}
inline std::string ascii_to_upper(std::string_view data) {
  return ascii_convert_impl::create_upper(data);
}
}// namespace string_utils
}// namespace vk

#endif// STRING_UTIL_H
