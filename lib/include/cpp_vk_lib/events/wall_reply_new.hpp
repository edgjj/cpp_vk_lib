#ifndef VK_WALL_REPLY_NEW_H
#define VK_WALL_REPLY_NEW_H

#include "events/handlers/attachment_handler.hpp"

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
 * It means, that no data is extracted from JSON until the user wants to access
 * it.
 */
class wall_reply_new {
public:
  wall_reply_new(const wall_reply_new&) = default;
  wall_reply_new(wall_reply_new&&) = default;
  wall_reply_new& operator=(const wall_reply_new&) = default;
  wall_reply_new& operator=(wall_reply_new&&) = default;
  ~wall_reply_new() = default;

  /*!
   * @brief Construct event from JSON.
   */
  explicit wall_reply_new(simdjson::dom::object&& event);
  /*!
   * @returns id field from _event_json;
   */
  std::int64_t id() const noexcept;
  /*!
   * @returns from_id field from _event_json;
   */
  std::int64_t from_id() const noexcept;
  /*!
   * @returns post_id field from _event_json;
   */
  std::int64_t post_id() const noexcept;
  /*!
   * @returns owner_id field from _event_json;
   */
  std::int64_t owner_id() const noexcept;
  /*!
   * @returns text field from _event_json;
   */
  std::string text() const noexcept;
  /*!
   * @returns true if event has attachments;
   */
  bool has_attachments() const noexcept;
  /*!
   * @brief Get attachments vector.
   * @throws vk::exception::access_error in case, when object hasn't
   * attachments.
   */
  attachment::attachments_t attachments() const;

private:
  simdjson::dom::object& get_event() const {
    return *_event_json;
  }

  std::shared_ptr<simdjson::dom::object> _event_json;
  bool _has_attachments = false;
  attachment_handler _attachment_handler;
};
}// namespace event
}// namespace vk

std::ostream& operator<<(std::ostream& ostream, const vk::event::wall_reply_new& reply);

#endif// VK_WALL_REPLY_NEW_H
