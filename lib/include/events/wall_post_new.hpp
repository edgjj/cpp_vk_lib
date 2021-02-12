#ifndef VK_WALL_POST_NEW_H
#define VK_WALL_POST_NEW_H

#include <string>

#include "events/handlers/attachment_handler.hpp"
#include "misc/cppdefs.hpp"


namespace simdjson {
namespace dom {
class object;
} // namespace dom
} // namespace simdjson

namespace vk {
namespace event {
class vk_export wall_post_new {
public:
    wall_post_new(std::string_view raw_json);
    std::int64_t id() const noexcept;
    std::int64_t from_id() const noexcept;
    std::int64_t owner_id() const noexcept;
    std::int64_t created_by() const noexcept;
    std::string text() const noexcept;
    attachment::attachments_t attachments() const noexcept;
    std::shared_ptr<wall_post_new> repost() const;
    bool can_edit() const noexcept;
    bool can_delete() const noexcept;
    bool marked_as_ads() const noexcept;

private:
    wall_post_new(const simdjson::dom::object& event);
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
