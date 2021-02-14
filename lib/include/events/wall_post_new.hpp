#ifndef VK_WALL_POST_NEW_H
#define VK_WALL_POST_NEW_H

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
class vk_export wall_post_new {
public:
  /*!
   * @brief Construct event from JSON.
   */
  wall_post_new(simdjson::dom::object&& event);
  std::int64_t id()           const noexcept;
  std::int64_t from_id()      const noexcept;
  std::int64_t owner_id()     const noexcept;
  std::int64_t created_by()   const noexcept;
  std::string text()          const noexcept;
  bool can_edit()             const noexcept;
  bool can_delete()           const noexcept;
  bool marked_as_ads()        const noexcept;
  /*!
   * @brief Try get repost.
   * @throws vk::exception::access_error in case, when _repost pointer is not set.
   */
  std::shared_ptr<wall_post_new> repost() const;
  /*!
   * @brief Get attachments vector.
   *
   * In case, when no attachments were provided, empty vector returned.
   */
  attachment::attachments_t attachments() const noexcept;

private:
  /*!
   * @brief Construct reply event.
   */
  wall_post_new(const simdjson::dom::object& event);
  /*!
   * @brief Common construct function.
   */
  void construct(const simdjson::dom::object& event, bool is_reply);

  static inline bool is_reply = true;
  static inline bool is_not_reply = false;

  std::int64_t _id;
  std::int64_t _from_id;
  std::int64_t _owner_id;
  std::int64_t _created_by;
  std::string _text;
  bool _can_edit;
  bool _can_delete;
  bool _marked_as_ads;
  std::shared_ptr<wall_post_new> _repost;
  attachment::attachments_t _attachments;

  attachment_handler _attachment_handler;
};
} // namespace event
} // namespace vk

#endif // VK_WALL_POST_NEW_H
