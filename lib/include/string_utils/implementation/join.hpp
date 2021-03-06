#ifndef STRING_UTIL_JOIN_IMPL_H
#define STRING_UTIL_JOIN_IMPL_H

#include <numeric>
#include <string>

#include "misc/cppdefs.hpp"


namespace vk {
namespace string_utils {
template <typename T, typename _Container>
std::string join(_Container&& elements, char delimiter = ',');
template <typename T>
std::string join(std::initializer_list<T> elements, char delimiter = ',');
} // namespace string_util
} // namespace vk

namespace vk {
namespace string_utils {

template <typename T>
struct join_implementation {
private:
  template <typename _Container, typename _Binary_operation>
  static std::string common_implementation(_Container&& elements, _Binary_operation operation) {
    return std::accumulate(elements.begin(), elements.end(), std::string(), operation);
  }
  template <typename _Container>
  static std::string common_create(_Container&& elements, char delimiter) {
    return common_implementation(elements, [&delimiter](std::string& accumlator, T element){
      if constexpr (std::is_integral_v<T>) {
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

  template <typename _Container>
  static std::string create(_Container&& elements, char delimiter) {
    return common_create<_Container&&>(elements, delimiter);
  }
  template <typename _T, typename _Container>
  friend std::string vk::string_utils::join(_Container&& elements, char delimiter);
  template <typename _T>
  friend std::string vk::string_utils::join(std::initializer_list<_T> elements, char delimiter);
};
} // namespace string_util
} // namespace vk

#endif // STRING_UTIL_JOIN_IMPL_H
