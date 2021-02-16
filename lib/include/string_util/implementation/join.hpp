#ifndef STRING_UTIL_JOIN_IMPL_H
#define STRING_UTIL_JOIN_IMPL_H

#include <numeric>
#include <string>

#include "misc/cppdefs.hpp"


namespace vk {
namespace string_util {
template <typename T, typename container>
std::string join(container&& elements, char delimiter = ',');
template <typename T>
std::string join(std::initializer_list<T> elements, char delimiter = ',');
} // namespace string_util
} // namespace vk

namespace vk {
namespace string_util {
template <typename T>
struct join_implementation {
private:
  using is_integral = std::true_type;
  using is_not_integral = std::false_type;

  template <typename container, typename binary_operation>
  static std::string common_implementation(container&& elements, binary_operation operation) {
    return std::accumulate(elements.begin(), elements.end(), std::string(), operation);
  }
  template <typename container>
  static std::string common_create(container&& elements, char delimiter) {
    return common_implementation(elements, [&delimiter](std::string& accumlator, T element){
      if constexpr (std::is_integral<T>()) {
        return accumlator.empty()
          ? std::to_string(element)
          : std::move(accumlator) + delimiter + std::to_string(element);
      } else {
        return accumlator.empty()
          ? std::string(element)
          : std::move(accumlator) + delimiter + std::string(element);
      }
    });
  }

  template <typename container>
  static std::string create(container&& elements, char delimiter) {
    return common_create<container&&>(elements, delimiter);
  }
  template <typename _T, typename _container>
  friend std::string vk::string_util::join(_container&& elements, char delimiter);
  template <typename _T>
  friend std::string vk::string_util::join(std::initializer_list<_T> elements, char delimiter);
};
} // namespace string_util
} // namespace vk

#endif // STRING_UTIL_JOIN_IMPL_H
