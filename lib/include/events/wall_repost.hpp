#ifndef VK_WALL_REPOST_H
#define VK_WALL_REPOST_H

#include "attachment/attachment.hpp"
#include "processing/process_error.hpp"


namespace vk {
namespace event {

/*!
 * @brief The `wall_post_new` repost representation.
 *
 * Internal information accessed in a "lazy way".
 * It means, that no data is extracted from JSON until the user wants to access it.
 */
class vk_export wall_repost {
public:
  wall_repost(std::int64_t id, std::int64_t from_id,
              std::int64_t owner_id, std::string text)
    : _id(id), _from_id(from_id), _owner_id(owner_id), _text(text)
  { }
  void construct_attachments(attachment::attachments_t&& attachments) {
    _attachments = attachments;
  }
  std::int64_t id() const noexcept { return _id; }
  std::int64_t from_id() const noexcept { return _from_id; }
  std::int64_t owner_id() const noexcept { return _owner_id; }
  std::string text() const noexcept { return _text; }
  attachment::attachments_t attachments() const { return _attachments; }

private:
  std::int64_t _id;
  std::int64_t _from_id;
  std::int64_t _owner_id;
  std::string _text;
  attachment::attachments_t _attachments;
};
} // namespace event
} // namespace vk

#endif //VK_WALL_REPOST_H
