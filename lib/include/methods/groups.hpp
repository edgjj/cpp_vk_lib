#ifndef VK_GROUPS_H
#define VK_GROUPS_H

#include "api/base_object.hpp"


namespace vk {
class VK_EXPORT groups : private base_object {
public:
    explicit groups(std::string_view user_token_) : base_object(user_token_) { };
    explicit groups() = default;
    ~groups() = default;

    std::int64_t get_by_id();
    simdjson::dom::object get_long_poll_server(std::string_view group_id);
};
} // namespace vk

#endif // VK_GROUPS_H
