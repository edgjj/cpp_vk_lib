#ifndef VK_EVENTS_MESSAGE_NEW_HPP
#define VK_EVENTS_MESSAGE_NEW_HPP

#include "vk/include/attachment/base.hpp"
#include "vk/include/events/action.hpp"

#include <vector>

namespace simdjson::dom {
class object;
class array;
}// namespace simdjson::dom

namespace vk::event {
/*!
 * @brief The `message_new` event representation.
 *
 * Internal information accessed in a "lazy way".
 * It means, that no data is extracted from JSON until the user wants to access
 * it, and there's meaningless to construct all attachment, reply and forwarded
 * messages objects in the case you only need message text.
 */
class message_new
{
public:
    message_new(simdjson::dom::object event);
    ~message_new();
    /*!
     * @throws vk::exception::access_error in case, when reply pointer is not set.
     */
    std::shared_ptr<message_new> reply() const;
    /*!
     * @throws vk::exception::access_error in case, when forward messages vector is empty.
     */
    std::vector<std::unique_ptr<message_new>> fwd_messages() const;
    /*!
     * @throws vk::exception::access error in case, when there's no actions setted.
     */
    action::any_action_t action() const;
    /*!
     * @throws exception::access_error in case, when object hasn't attachments.
     * @note In case, when no attachments were provided, empty vector returned.
     */
    std::vector<attachment::attachment_ptr_t> attachments() const;

    bool on_action(std::string_view action_type) const noexcept;

    int64_t conversation_message_id() const noexcept;
    std::string text() const noexcept;
    int64_t from_id() const noexcept;
    int64_t peer_id() const noexcept;
    bool has_reply() const noexcept;
    bool has_fwd_messages() const noexcept;
    bool has_action() const noexcept;

private:
    void try_get_actions();
    simdjson::dom::object& get_event() const;

    std::shared_ptr<simdjson::dom::object> event_json_;
    action::any_action_t action_;
    bool has_action_ = false;
    bool has_reply_ = false;
    bool has_fwd_messages_ = false;
    bool has_attachments_ = false;
};

}// namespace vk::event

std::ostream& operator<<(std::ostream& ostream, const vk::event::message_new& event);

#endif// VK_EVENTS_MESSAGE_NEW_HPP
