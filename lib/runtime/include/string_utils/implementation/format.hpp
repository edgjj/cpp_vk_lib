#ifndef VK_STRING_UTILS_IMPLEMENTATION_FORMAT_HPP
#define VK_STRING_UTILS_IMPLEMENTATION_FORMAT_HPP

#include <array>
#include <sstream>

namespace runtime {
namespace string_utils {
template <typename... Args>
std::string format(std::string_view data, Args&&... args);
}// namespace string_utils
}// namespace runtime

namespace runtime {
namespace string_utils {

template <typename... Args>
struct format_impl
{
public:
    format_impl() = delete;

private:
    static constexpr size_t average_word_size = 7;

    static std::string create(std::string_view data, Args&&... args)
    {
        if (data.empty()) { return {}; }

        std::string formatted;
        formatted.reserve(data.size() + (average_word_size * sizeof...(args)));
        auto pack_one = [](auto&& argument) {
            if constexpr (std::is_integral_v<std::decay_t<decltype(argument)>>) {
                return std::to_string(argument);
            } else {
                return std::string(argument);
            }
        };
        std::array<std::string, sizeof...(Args)> elements{pack_one(args)...};
        size_t curr = 0;
        for (size_t i = 0; i < data.size(); i++) {
            // If we're have '{}' token, insert parameter at this place.
            if (data[i] == '{' && data[i + 1] == '}') {
                formatted += elements[curr++];
                // Add all characters from source string except '{}' token.
            } else if (data[i - 1] != '{' || data[i] != '}') {
                formatted += data[i];
            }
        }
        return formatted;
    }

    template <typename... mArgs>
    friend std::string runtime::string_utils::format(std::string_view data, mArgs&&... args);
};

}// namespace string_utils
}// namespace runtime

#endif// VK_STRING_UTILS_IMPLEMENTATION_FORMAT_HPP
