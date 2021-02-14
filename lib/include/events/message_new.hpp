#ifndef VK_MESSAGE_NEW_H
#define VK_MESSAGE_NEW_H

#include "events/handlers/attachment_handler.hpp"
#include "events/handlers/message_action_handler.hpp"

#include "events/handlers/message_new_data.hpp"


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
 */
class vk_export message_new {
public:
  /*!
   * @brief Construct event from JSON.
   */
  message_new(simdjson::dom::object&& event);
  /*!
   * @brief Construct reply or forwarded message.ы
   */
  message_new(
    std::int64_t peer_id, std::int64_t from_id, std::string_view text,
    simdjson::dom::array&& attachments
  );

  /*!
   * @brief Try get reply.
   * @throws vk::exception::access_error in case, when reply pointer is not set.
   */
  message_new reply() const;
  /*!
   * @brief Try get reply.
   * @throws vk::exception::access_error in case, when forward messages vector is empty.
   */
  std::vector<std::shared_ptr<message_new>> fwd_messages() const;

  /*!
   * @brief Check if message has requested action type.
   */
  bool on_action(std::string_view action_name) const noexcept;

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
  void try_get_reply          (const simdjson::dom::object& reply);
  void try_get_fwd_messages   (const simdjson::dom::array& messages);
  void try_get_actions        (const simdjson::dom::object& action);

  std::shared_ptr<message_new_data> _message_obj;
  std::shared_ptr<message_new> _reply;
  action::any_action _action;
  std::vector<std::shared_ptr<message_new>> _fwd_messages;
  attachment::attachments_t _attachments;
  bool _has_action = false;
  bool _has_reply = false;
  bool _has_fwd_messages = false;

  attachment_handler att_handler;
};
} // namespace event
} // namespace vk

#endif // VK_MESSAGE_NEW_H
