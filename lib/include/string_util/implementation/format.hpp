#ifndef STRING_UTIL_FORMAT_IMPL_H
#define STRING_UTIL_FORMAT_IMPL_H

#include <deque>
#include <array>
#include <sstream>
#include <any>

#include "misc/cppdefs.hpp"


namespace vk {
namespace string_util {
template <typename... Args>
std::string format(std::string_view str, Args&&... args);
} // namespace string_util
} // namespace vk

namespace vk {
namespace string_util {
template <typename... Args> struct vk_hidden format_implementation {
private:
    static std::string create(std::string_view str, Args&&... args) {
        std::string formatted;
        std::ostringstream ss;
        auto packOne = [&ss](auto&& arg) {
            ss.str("");
            ss.clear();
            ss << std::forward<decltype(arg)>(arg);
            return ss.str();
        };
        std::array<std::string, sizeof...(Args)> elements{packOne(args)...};
        std::size_t curr = 0;
        for (std::size_t i = 0; i < str.size(); i++) {
            if (str[i] == '{' && str[i + 1] == '}') {
                formatted += elements[curr++];
            } else if (str[i - 1] != '{' || str[i] != '}') {
                formatted += str[i];
            }
        }
        return formatted;
    }

    template <typename... _Args>
    friend std::string format(std::string_view str, _Args&&... args);
};
} // namespace string_util
} // namespace vk

#endif // STRING_UTIL_FORMAT_IMPL_H
