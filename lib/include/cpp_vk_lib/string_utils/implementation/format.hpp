#ifndef STRING_UTIL_FORMAT_IMPL_H
#define STRING_UTIL_FORMAT_IMPL_H

#include <any>
#include <array>
#include <deque>
#include <sstream>

namespace vk {
namespace string_utils {
template <typename... _Args>
std::string format(std::string_view data, _Args&&... args);
}// namespace string_utils
}// namespace vk

namespace vk {
namespace string_utils {

template <typename... _Args>
struct format_impl
{
public:
    format_impl() = delete;

private:
    static constexpr std::size_t average_word_size = 7;

    static std::string create(std::string_view data, _Args&&... args)
    {
        if (data.empty())
            return {};
        std::string formatted;
        formatted.reserve(data.size() + (average_word_size * sizeof...(args)));
        auto pack_one = [](auto&& argument) {
            if constexpr (std::is_integral_v<std::decay_t<decltype(argument)>>)
            {
                return std::to_string(argument);
            }
            else
            {
                return std::string(argument);
            }
        };
        std::array<std::string, sizeof...(_Args)> elements{pack_one(args)...};
        std::size_t curr = 0;
        for (std::size_t i = 0; i < data.size(); i++)
        {
            // If we're have '{}' token, insert parameter at this place.
            if (data[i] == '{' && data[i + 1] == '}')
            {
                formatted += elements[curr++];
                // Add all characters from source string except '{}' token.
            }
            else if (data[i - 1] != '{' || data[i] != '}')
            {
                formatted += data[i];
            }
        }
        return formatted;
    }

    template <typename... __Args>
    friend std::string vk::string_utils::format(std::string_view data, __Args&&... args);
};
}// namespace string_utils
}// namespace vk

#endif// STRING_UTIL_FORMAT_IMPL_H
