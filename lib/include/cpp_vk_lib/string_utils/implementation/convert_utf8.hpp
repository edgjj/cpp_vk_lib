#ifndef STRING_UTIL_UTF8_CONVERT_H
#define STRING_UTIL_UTF8_CONVERT_H

#include <codecvt>
#include <locale>


namespace vk {
namespace string_utils {
std::string utf8_to_lower(std::string_view data);
std::string utf8_to_upper(std::string_view data);
} // namespace string_util
} // namespace vk

namespace vk {
namespace string_utils {

const std::locale utf8("en_US.UTF-8");

struct utf8_convert_impl {
private:
  static std::wstring __to_wstring(const std::string& s) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    return conv.from_bytes(s);
  }
  static std::string __to_string(const std::wstring& s) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    return conv.to_bytes(s);
  }
  template <typename _Execution_Policy>
  static std::string __create(std::string_view data, _Execution_Policy policy) {
    auto ss = __to_wstring(data.data());
    for (auto& c : ss) {
      c = policy(c);
    }
    return __to_string(ss);
  }
  static std::string create_upper(std::string_view data) {
    return __create(data, [](auto& c){
      return std::toupper(c, utf8);
    });
  }
  static std::string create_lower(std::string_view data) {
    return __create(data, [](auto& c){
      return std::tolower(c, utf8);
    });
  }
  friend std::string string_utils::utf8_to_lower(std::string_view data);
  friend std::string string_utils::utf8_to_upper(std::string_view data);
};

} // namespace string_utils
} // namespace vk

#endif // STRING_UTIL_UTF8_CONVERT_H
