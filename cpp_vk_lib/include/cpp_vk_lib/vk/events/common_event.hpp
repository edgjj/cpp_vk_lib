#ifndef VK_EVENTS_COMMON_EVENT_HPP
#define VK_EVENTS_COMMON_EVENT_HPP

#include <string>
#include <memory>

namespace vk::event {
class message_new;
class wall_post_new;
class wall_reply_new;
}// namespace vk::event

namespace simdjson::dom {
class object;
}// namespace simdjson::dom

namespace vk::event {
/*!
 * @brief Temporary update container.
 */
class common
{
public:
    common(std::string_view ts, simdjson::dom::object event);
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

    std::string ts_;
    std::string update_type_;
    std::shared_ptr<simdjson::dom::object> event_;
};

}// namespace vk::event

#endif// VK_EVENTS_COMMON_EVENT_HPP
