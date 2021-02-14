#ifndef STRING_UTIL_OSTREAM_OPERATORS_H
#define STRING_UTIL_OSTREAM_OPERATORS_H

#include <codecvt>
#include <locale>


std::ostream& operator<<(std::ostream& os, std::wstring_view s) {
  return os << std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().to_bytes(s.data());
}
std::ostream& operator<<(std::ostream& os, std::u16string_view s) {
  return os << std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t>().to_bytes(s.data());
}
std::ostream& operator<<(std::ostream& os, std::u32string_view s) {
  return os << std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().to_bytes(s.data());
}

#endif // STRING_UTIL_OSTREAM_OPERATORS_H
