#ifndef VK_UTILS_H
#define VK_UTILS_H

#include "api/base_object.hpp"


namespace vk
{
class VK_EXPORT utils : private base_object
{
public:
    bool check_link                 (std::string_view url);
    std::string get_short_link      (std::string_view url);
    std::int64_t resolve_screen_name(std::string_view screen_name);
};
} // namespace vk

#endif // VK_UTILS_H
