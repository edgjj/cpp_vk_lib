#ifndef RUNTIME_STRING_UTILS_IMPLEMENTATION_CONVERT_ASCII_HPP
#define RUNTIME_STRING_UTILS_IMPLEMENTATION_CONVERT_ASCII_HPP

#include <codecvt>
#include <locale>

namespace runtime {
namespace string_utils {
namespace implementation {

template <typename ExecutionPolicy>
static inline std::string ascii_convert_implementation(std::string_view data, ExecutionPolicy policy)
{
    std::string converted;
    converted.reserve(data.length());

    for (auto& c : data) {
        converted += policy(c);
    }

    return converted;
}

inline std::string create_ascii_lower(std::string_view data)
{
    return ascii_convert_implementation(data, [](auto c) -> char {
        if (c <= 'Z' && c >= 'A') {
            return c - ('Z' - 'z');
        }

        return c;
    });
}

inline std::string create_ascii_upper(std::string_view data)
{
    return ascii_convert_implementation(data, [](auto& c) -> char {
        if (c <= 'z' && c >= 'a') {
            return c + ('Z' - 'z');
        }

        return c;
    });
}

}// namespace implementation
}// namespace string_utils
}// namespace runtime

#endif// RUNTIME_STRING_UTILS_IMPLEMENTATION_CONVERT_ASCII_HPP
