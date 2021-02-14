#ifndef VK_COMMON_EVENT_H
#define VK_COMMON_EVENT_H

#include "events/message_new.hpp"
#include "events/wall_post_new.hpp"
#include "events/wall_reply_new.hpp"


namespace simdjson {
namespace dom {
class object;
} // namespace dom
} // namespace simdjson

namespace vk {
namespace event {
class vk_export common {
public:
    common(std::string_view ts, simdjson::dom::object&& event);

    std::string type() const noexcept;
    std::string ts()   const noexcept;
    std::string dump() const noexcept;

    bool on_type(std::string_view type) const noexcept;
    message_new get_message_event() const;
    wall_post_new get_wall_post_event() const;
    wall_reply_new get_wall_reply_event() const;

private:
    std::string _ts;
    std::string _update_type;
    std::unique_ptr<simdjson::dom::object> _event;
};
} // namespace event
} // namespace vk

#endif // VK_COMMON_EVENT_H
