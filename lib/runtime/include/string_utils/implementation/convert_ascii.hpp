#ifndef VK_STRING_UTILS_IMPLEMENTATION_CONVERT_ASCII_HPP
#define VK_STRING_UTILS_IMPLEMENTATION_CONVERT_ASCII_HPP

#include <codecvt>
#include <locale>

namespace runtime {
namespace string_utils {
std::string ascii_to_lower(std::string_view data);
std::string ascii_to_upper(std::string_view data);
}// namespace string_utils
}// namespace runtime

namespace runtime {
namespace string_utils {

struct ascii_convert_impl
{
private:
    static char internal_to_lower_ascii_char(char c) noexcept
    {
        if (c <= 'Z' && c >= 'A') {
            return c - ('Z' - 'z');
        }

        return c;
    }

    static char internal_to_upper_ascii_char(char c) noexcept
    {
        if (c <= 'z' && c >= 'a') {
            return c + ('Z' - 'z');
        }

        return c;
    }

    template <typename ExecutionPolicy>
    static std::string internal_ascii_convert_implementation(std::string_view data, ExecutionPolicy policy)
    {
        std::string converted;
        converted.reserve(data.length());

        for (auto& c : data) {
            converted += policy(c);
        }

        return converted;
    }

    static std::string create_lower(std::string_view data)
    {
        return internal_ascii_convert_implementation(data, [](auto& c) {
            return internal_to_lower_ascii_char(c);
        });
    }

    static std::string create_upper(std::string_view data)
    {
        return internal_ascii_convert_implementation(data, [](auto& c) {
            return internal_to_upper_ascii_char(c);
        });
    }

    friend std::string string_utils::ascii_to_lower(std::string_view data);
    friend std::string string_utils::ascii_to_upper(std::string_view data);
};

}// namespace string_utils
}// namespace runtime

#endif// VK_STRING_UTILS_IMPLEMENTATION_CONVERT_ASCII_HPP
