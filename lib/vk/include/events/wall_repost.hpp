#ifndef VK_EVENTS_WALL_REPOST_HPP
#define VK_EVENTS_WALL_REPOST_HPP

#include "vk/include/attachment/attachment.hpp"

namespace vk {
namespace event {
/*!
 * @brief The `wall_post_new` repost representation.
 *
 * Internal information accessed in a "lazy way".
 * It means, that no data is extracted from JSON until the user wants to access
 * it.
 */
class wall_repost
{
public:
    wall_repost(int64_t id, int64_t from_id, int64_t owner_id, std::string text);

    void construct_attachments(attachment::attachments_t&& attachments);

    int64_t id() const noexcept;
    int64_t from_id() const noexcept;
    int64_t owner_id() const noexcept;
    const std::string& text() const noexcept;
    const attachment::attachments_t& attachments() const noexcept;

private:
    int64_t m_id;
    int64_t m_from_id;
    int64_t m_owner_id;
    std::string m_text;
    attachment::attachments_t m_attachments;
};

}// namespace event
}// namespace vk

#endif// VK_EVENTS_WALL_REPOST_HPP
