#ifndef STRING_UTIL_FORMAT_IMPL_H
#define STRING_UTIL_FORMAT_IMPL_H

#include <deque>
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
struct vk_hidden any_stream : public std::any {
    void(*streamer)(std::ostream&, any_stream const&) = nullptr;
    friend std::ostream& operator<<(std::ostream& os, const any_stream& a) {
        a.streamer(os, a);
        return os;
    }
    template<class T, std::enable_if_t<!std::is_same<std::decay_t<T>, any_stream>{}, bool> = true>
    any_stream(T&& t)
        : std::any(std::forward<T>(t))
        , streamer([](std::ostream& os, const any_stream& self) {
            os << std::any_cast<std::decay_t<T>>(self);
        })
    { }
};

template <typename... Args> struct vk_hidden format_implementation {
private:
    static void pack(std::deque<any_stream>& container, Args&&... args) {
        ([&container](auto& input){ container.push_back(input); } (args), ...);
    }
    static std::string create(std::string_view str, Args&&... args) {
        std::stringstream formatted;
        std::deque<any_stream> elements;
        pack(elements, std::forward<Args>(args)...);
        for (std::size_t i = 0; i < str.size(); i++) {
            if (str[i] == '{' && str[i + 1] == '}') {
                formatted << elements.front();
                elements.pop_front();
            } else if (str[i - 1] != '{' || str[i] != '}') {
                formatted << str[i];
            }
        }
        return formatted.str();
    }

    template <typename... _Args>
    friend std::string format(std::string_view str, _Args&&... args);
};
} // namespace string_util
} // namespace vk

#endif // STRING_UTIL_FORMAT_IMPL_H
