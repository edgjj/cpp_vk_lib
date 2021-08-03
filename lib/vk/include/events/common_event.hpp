#ifndef VK_EVENTS_COMMON_EVENT_HPP
#define VK_EVENTS_COMMON_EVENT_HPP

#include <string>
#include <memory>

namespace vk {
namespace event {
class message_new;
class wall_post_new;
class wall_reply_new;
}// namespace event
}// namespace vk

namespace simdjson {
namespace dom {
class object;
}// namespace dom
}// namespace simdjson

namespace vk {
namespace event {
/*!
 * @brief Temporary update container.
 */
class common
{
public:
    common(std::string_view ts, simdjson::dom::object&& event);
    ~common();

    std::string type() const noexcept;
    std::string ts() const noexcept;
    std::string dump() const noexcept;

    bool on_type(std::string_view type) const noexcept;

    explicit operator message_new() const;
    explicit operator wall_post_new() const;
    explicit operator wall_reply_new() const;

    message_new get_message_new() const;
    wall_post_new get_wall_post_new() const;
    wall_reply_new get_wall_reply_new() const;

private:
    simdjson::dom::object& get_event() const noexcept;

    std::string m_ts;
    std::string m_update_type;
    std::shared_ptr<simdjson::dom::object> m_event;
};

}// namespace event
}// namespace vk

#endif// VK_EVENTS_COMMON_EVENT_HPP
