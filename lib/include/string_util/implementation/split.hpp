#ifndef STRING_UTIL_SPLIT_IMPL_H
#define STRING_UTIL_SPLIT_IMPL_H

#include <vector>
#include <string_view>

#include "misc/cppdefs.hpp"


namespace vk {
namespace string_util {
std::vector<std::string_view> split(std::string_view text, char delimiter) noexcept;
} // namespace string_util
} // namespace vk

namespace vk {
namespace string_util {
struct VK_HIDDEN split_implementation {
private:
    static std::vector<std::string_view> create(std::string_view text, char delimiter) noexcept {
        std::vector<std::string_view> splitted;
        splitted.reserve(text.length() / 4);
        std::size_t pos = 0;

        while (pos != std::string_view::npos) {
            pos = text.find_first_not_of(delimiter);
            if (pos == std::string_view::npos)
                return splitted;
            text = text.substr(pos);
            pos = text.find(delimiter);
            splitted.emplace_back(text.substr(0, pos));
            text = text.substr(pos == std::string_view::npos ? 0 : pos);
        }
        splitted.shrink_to_fit();
        return splitted;
    }

    friend std::vector<std::string_view> vk::string_util::split(std::string_view text, char delimiter) noexcept;
};
} // namespace string_util
} // namespace vk

#endif // STRING_UTIL_SPLIT_IMPL_H
