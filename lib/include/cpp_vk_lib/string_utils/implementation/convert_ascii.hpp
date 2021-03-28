#ifndef STRING_UTIL_ASCII_CONVERT_H
#define STRING_UTIL_ASCII_CONVERT_H

#include <codecvt>
#include <locale>


namespace vk {
namespace string_utils {
std::string ascii_to_lower(std::string_view data);
std::string ascii_to_upper(std::string_view data);
} // namespace string_util
} // namespace vk

namespace vk {
namespace string_utils {

struct ascii_convert_impl {
private:
  static char __to_lower_ascii_char(char c) noexcept {
    if (c <= 'Z' && c >= 'A') {
      return c - ('Z' - 'z');
    }
    return c;
  }

  static char __to_upper_ascii_char(char c) noexcept {
    if (c <= 'z' && c >= 'a') {
      return c + ('Z' - 'z');
    }
    return c;
  }
  template <typename _Execution_Policy>
  static std::string __ascii_convert_implementation(std::string_view data, _Execution_Policy policy) {
    std::string converted;
    converted.reserve(data.length());
    for (auto& c : data) {
      converted += policy(c);
    }
    return converted;
  }
  static std::string create_lower(std::string_view data) {
    return __ascii_convert_implementation(data, [](auto& c) {
      return __to_lower_ascii_char(c);
    });
  }
  static std::string create_upper(std::string_view data) {
    return __ascii_convert_implementation(data, [](auto& c) {
      return __to_upper_ascii_char(c);
    });
  }
  friend std::string string_utils::ascii_to_lower(std::string_view data);
  friend std::string string_utils::ascii_to_upper(std::string_view data);
};

} // namespace string_utils
} // namespace vk

#endif // STRING_UTIL_ASCII_CONVERT_H
