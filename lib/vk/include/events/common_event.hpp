#ifndef VK_EVENTS_COMMON_EVENT_HPP
#define VK_EVENTS_COMMON_EVENT_HPP

#include "vk/include/events/message_new.hpp"
#include "vk/include/events/wall_post_new.hpp"
#include "vk/include/events/wall_reply_new.hpp"

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

    /*!
     * @brief Check if event matches @param type.
     */
    bool on_type(std::string_view type) const noexcept;

    message_new get_message_event() const;
    wall_post_new get_wall_post_event() const;
    wall_reply_new get_wall_reply_event() const;

private:
    simdjson::dom::object& get_event() const noexcept;

    std::string m_ts;
    std::string m_update_type;
    std::shared_ptr<simdjson::dom::object> m_event;
};

}// namespace event
}// namespace vk

#endif// VK_EVENTS_COMMON_EVENT_HPP
