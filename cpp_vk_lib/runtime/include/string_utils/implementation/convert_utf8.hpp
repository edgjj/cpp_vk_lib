#ifndef RUNTIME_STRING_UTILS_IMPLEMENTATION_CONVERT_UTF8_HPP
#define RUNTIME_STRING_UTILS_IMPLEMENTATION_CONVERT_UTF8_HPP

#include <codecvt>
#include <locale>

namespace runtime::string_utils::implementation {

const std::locale utf8("en_US.UTF-8");

template <typename ExecutionPolicy>
static inline std::string utf8_create(std::string_view data, ExecutionPolicy converter)
{
    std::wstring wide_string = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(data.data());
    for (auto& c : wide_string) {
        c = converter(c);
    }
    return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(wide_string);
}

inline std::string create_utf8_upper(std::string_view data)
{
    return utf8_create(data, [](auto& c) {
        return std::toupper(c, utf8);
    });
}

inline std::string create_utf8_lower(std::string_view data)
{
    return utf8_create(data, [](auto& c) {
        return std::tolower(c, utf8);
    });
}

}// namespace runtime::string_utils::implementation

#endif// RUNTIME_STRING_UTILS_IMPLEMENTATION_CONVERT_UTF8_HPP
