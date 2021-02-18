#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include "string_utils/implementation/format.hpp"
#include "string_utils/implementation/join.hpp"
#include "string_utils/implementation/split.hpp"
#include "string_utils/implementation/lazy_split.hpp"


namespace vk {
namespace string_utils {

template <typename T, typename container>
std::string join(container&& elements, char delimiter) {
  return join_implementation<T>::create(elements, delimiter);
}
template <typename T>
std::string join(std::initializer_list<T> elements, char delimiter) {
  return join_implementation<T>::create(elements, delimiter);
}
template <typename... Args>
std::string format(std::string_view data, Args&&... args) {
  return format_implementation<Args...>::create(data, std::forward<Args>(args)...);
}
inline std::vector<std::string_view> split(std::string_view data, char delimiter) {
  return split_implementation::create(data, delimiter);
}
inline auto lazy_split(std::string_view data, std::string_view delimiter) {
  return split_range<std::string_view>(data, delimiter);
}
} // namespace string_util
} // namespace vk

#endif // STRING_UTIL_H
