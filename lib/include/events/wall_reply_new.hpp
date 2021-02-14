#ifndef VK_WALL_REPLY_NEW_H
#define VK_WALL_REPLY_NEW_H

#include "events/handlers/attachment_handler.hpp"


namespace simdjson {
namespace dom {
class object;
} // namespace dom
} // namespace simdjson

namespace vk {
namespace event {
/*!
 * @brief The `wall_post_new` event representation.
 */
class vk_export wall_reply_new {
public:
  /*!
   * @brief Construct event from JSON.
   */
  explicit wall_reply_new(simdjson::dom::object&& event);
  std::int64_t id() const noexcept;
  std::int64_t from_id() const noexcept;
  std::int64_t post_id() const noexcept;
  std::int64_t owner_id() const noexcept;
  std::string text() const noexcept;
  /*!
   * @brief Get attachments vector.
   *
   * In case, when no attachments were provided, empty vector returned.
   */
  attachment::attachments_t attachments() const noexcept;

private:
  std::int64_t _id;
  std::int64_t _post_id;
  std::int64_t _from_id;
  std::int64_t _owner_id;
  std::string _text;
  attachment::attachments_t _attachments;

  attachment_handler att_handler;
};
} // namespace event
} // namespace vk

#endif // VK_WALL_REPLY_NEW_H
