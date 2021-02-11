#ifndef VK_WALL_POST_NEW_H
#define VK_WALL_POST_NEW_H

#include <string_view>

#include "misc/cppdefs.hpp"


namespace vk {
namespace event {
class vk_export wall_post_new {
public:
    wall_post_new(std::string_view raw_json);
    std::int64_t id()      const noexcept;
    std::int64_t from_id() const noexcept;

private:
    std::int64_t _id;
    std::int64_t _from_id;
};
} // namespace event
} // namespace vk

#endif // VK_WALL_POST_NEW_H
