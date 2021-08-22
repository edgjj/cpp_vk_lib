#ifndef RUNTIME_STRING_UTILS_IMPLEMENTATION_CONVERT_ASCII_HPP
#define RUNTIME_STRING_UTILS_IMPLEMENTATION_CONVERT_ASCII_HPP

#include <codecvt>
#include <locale>

// template <typename ExecutionPolicy>
// static inline std::string
//    ascii_convert_impl(std::string_view data, ExecutionPolicy policy)
//{
//    std::string converted;
//    converted.reserve(data.length());
//
//    for (auto& c : data) {
//        converted += policy(c);
//    }
//
//    return converted;
//}

namespace runtime::string_utils {

inline std::string ascii_to_lower(std::string_view data)
{
    std::string converted;
    converted.reserve(data.length());
    for (char c : data) {
        if (c <= 'Z' && c >= 'A') {
            converted.push_back(char(c - ('Z' - 'z')));
        } else {
            converted.push_back(c);
        }
    }
    return converted;
}

inline std::string ascii_to_upper(std::string_view data)
{
    std::string converted;
    converted.reserve(data.length());
    for (char c : data) {
        if (c <= 'z' && c >= 'a') {
            converted.push_back(char(c + ('Z' - 'z')));
        } else {
            converted.push_back(c);
        }
    }
    return converted;
}

}// namespace runtime::string_utils

#endif// RUNTIME_STRING_UTILS_IMPLEMENTATION_CONVERT_ASCII_HPP
