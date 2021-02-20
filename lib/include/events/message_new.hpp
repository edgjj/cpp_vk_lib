#ifndef VK_MESSAGE_NEW_H
#define VK_MESSAGE_NEW_H

#include "events/handlers/attachment_handler.hpp"
#include "events/handlers/message_action_handler.hpp"


namespace simdjson {
namespace dom {
class object;
class array;
} // namespace dom
} // namespace simdjson

namespace vk {
namespace event {
/*!
 * @brief The `message_new` event representation.
 *
 * Internal information accessed in a "lazy way".
 * It means, that no data is parsed from JSON until the user wants to access it,
 * and there's meaningless to construct all attachment, reply and forwarded messages objects
 * in the case you only need message text.
 */
class vk_export message_new {
public:
  message_new(const message_new& other) = default;
  message_new(message_new&&) = default;

  /*!
   * @brief Construct event from JSON.
   */
  message_new(simdjson::dom::object&& event);
  /*!
   * @brief Try get reply.
   * @throws vk::exception::access_error in case, when reply pointer is not set.
   */
  std::shared_ptr<message_new> reply();
  /*!
   * @brief Try get reply.
   * @throws vk::exception::access_error in case, when forward messages vector is empty.
   */
  std::vector<std::unique_ptr<message_new>> fwd_messages() const;

  /*!
   * @brief Check if message has requested action type.
   */
  bool on_action(std::string_view action_type) const noexcept;

  std::int64_t conversation_message_id() const noexcept;
  std::string text()      const noexcept;
  std::int64_t from_id()  const noexcept;
  std::int64_t peer_id()  const noexcept;
  bool has_reply()        const noexcept;
  bool has_fwd_messages() const noexcept;
  bool has_action()       const noexcept;
  /*!
   * @brief Try get action.
   * @throws vk::exception::access error in case, when there's no actions setted.
   */
  action::any_action action() const;
  /*!
   * @brief Get attachments vector.
   *
   * In case, when no attachments were provided, empty vector returned.
   */
  attachment::attachments_t attachments() const;

private:
  void try_get_actions();

  std::shared_ptr<simdjson::dom::object> _message_json;
  action::any_action _action;
  bool _has_action = false;
  bool _has_reply = false;
  bool _has_fwd_messages = false;
  bool _has_attachments = false;

  attachment_handler att_handler;
};
} // namespace event
} // namespace vk

#endif // VK_MESSAGE_NEW_H
