#ifndef VK_WALL_POST_NEW_H
#define VK_WALL_POST_NEW_H

#include "events/handlers/attachment_handler.hpp"
#include "events/wall_repost.hpp"


namespace simdjson {
namespace dom {
class object;
} // namespace dom
} // namespace simdjson

namespace vk {
namespace event {
/*!
 * @brief The `wall_post_new` event representation.
 *
 * Internal information accessed in a "lazy way".
 * It means, that no data is extracted from JSON until the user wants to access it.
 */
class vk_export wall_post_new {
public:
  wall_post_new(const wall_post_new&) = default;
  wall_post_new(wall_post_new&&) = default;
  /*!
   * @brief Construct event from JSON.
   */
  wall_post_new(simdjson::dom::object&& event);
  /*!
   * @returns id field from _event_json;
   */
  std::int64_t id() const noexcept;
  /*!
   * @returns from_id field from _event_json;
   */
  std::int64_t from_id() const noexcept;
  /*!
   * @returns owner_id field from _event_json;
   */
  std::int64_t owner_id() const noexcept;
  /*!
   * @returns created_by field from _event_json;
   */
  std::int64_t created_by() const noexcept;
  /*!
   * @returns text field from _event_json;
   */
  std::string text() const noexcept;
  /*!
   * @returns can_edit field from _event_json;
   */
  bool can_edit() const noexcept;
  /*!
   * @returns can_delete field from _event_json;
   */
  bool can_delete() const noexcept;
  /*!
   * @returns marked_as_ads field from _event_json;
   */
  bool marked_as_ads() const noexcept;
  /*!
   * @brief Try get repost.
   * @throws vk::exception::access_error in case, when _repost pointer is not set.
   */
  std::shared_ptr<wall_repost> repost() const;
  /*!
   * @brief Get attachments vector.
   *
   * In case, when no attachments were provided, empty vector returned.
   */
  attachment::attachments_t attachments() const noexcept;

private:
  std::shared_ptr<simdjson::dom::object> _event_json;
  attachment_handler _attachment_handler;
  bool _has_attachments = false;
  bool _has_repost = false;
};
} // namespace event
} // namespace vk

#endif // VK_WALL_POST_NEW_H
