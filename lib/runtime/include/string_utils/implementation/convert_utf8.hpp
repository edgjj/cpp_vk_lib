#ifndef RUNTIME_STRING_UTILS_IMPLEMENTATION_CONVERT_UTF8_HPP
#define RUNTIME_STRING_UTILS_IMPLEMENTATION_CONVERT_UTF8_HPP

#include <codecvt>
#include <locale>

namespace runtime {
namespace string_utils {
std::string utf8_to_lower(std::string_view data);
std::string utf8_to_upper(std::string_view data);
}// namespace string_utils
}// namespace runtime

namespace runtime {
namespace string_utils {

const std::locale utf8("en_US.UTF-8");

struct utf8_convert_impl
{
private:
    static std::wstring internal_to_wstring(const std::string& s)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
        return conv.from_bytes(s);
    }
    static std::string internal_to_string(const std::wstring& s)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
        return conv.to_bytes(s);
    }
    template <typename ExecutionPolicy>
    static std::string internal_create(std::string_view data, ExecutionPolicy converter)
    {
        auto ss = internal_to_wstring(data.data());
        for (auto& c : ss) {
            c = converter(c);
        }
        return internal_to_string(ss);
    }
    static std::string create_upper(std::string_view data)
    {
        return internal_create(data, [](auto& c) {
            return std::toupper(c, utf8);
        });
    }
    static std::string create_lower(std::string_view data)
    {
        return internal_create(data, [](auto& c) {
            return std::tolower(c, utf8);
        });
    }
    friend std::string string_utils::utf8_to_lower(std::string_view data);
    friend std::string string_utils::utf8_to_upper(std::string_view data);
};

}// namespace string_utils
}// namespace runtime

#endif// RUNTIME_STRING_UTILS_IMPLEMENTATION_CONVERT_UTF8_HPP
