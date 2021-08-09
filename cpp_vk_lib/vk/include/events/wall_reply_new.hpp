#ifndef VK_EVENTS_WALL_REPLY_NEW_HPP
#define VK_EVENTS_WALL_REPLY_NEW_HPP

#include "vk/include/attachment/attachment.hpp"

#include  <vector>

namespace simdjson {
namespace dom {
class object;
}// namespace dom
}// namespace simdjson

namespace vk {
namespace event {
/*!
 * @brief The `wall_reply_new` event representation.
 *
 * Internal information accessed in a "lazy way".
 * It means, that no data is extracted from JSON until the user wants to access it.
 */
class wall_reply_new
{
public:
    explicit wall_reply_new(simdjson::dom::object event);
    ~wall_reply_new();

    int64_t id() const noexcept;
    int64_t from_id() const noexcept;
    int64_t post_id() const noexcept;
    int64_t owner_id() const noexcept;
    std::string text() const noexcept;
    bool has_attachments() const noexcept;
    std::vector<attachment::attachment_ptr_t> attachments() const;

private:
    simdjson::dom::object& get_event() const;

    std::shared_ptr<simdjson::dom::object> event_json_;
    bool has_attachments_ = false;
};

}// namespace event
}// namespace vk

std::ostream& operator<<(std::ostream& ostream, const vk::event::wall_reply_new& reply);

#endif// VK_EVENTS_WALL_REPLY_NEW_HPP
