#ifndef VK_WALL_REPOST_H
#define VK_WALL_REPOST_H

#include "attachment/attachment.hpp"

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
    wall_repost(std::int64_t id, std::int64_t from_id, std::int64_t owner_id, std::string text)
      : m_id(id)
      , m_from_id(from_id)
      , m_owner_id(owner_id)
      , m_text(text)
      , m_attachments()
    {}
    wall_repost(const wall_repost&) = default;
    wall_repost(wall_repost&&) = default;
    wall_repost& operator=(const wall_repost&) = default;
    wall_repost& operator=(wall_repost&&) = default;
    ~wall_repost() = default;

    void construct_attachments(attachment::attachments_t&& attachments)
    {
        m_attachments = attachments;
    }
    std::int64_t id() const noexcept
    {
        return m_id;
    }
    std::int64_t from_id() const noexcept
    {
        return m_from_id;
    }
    std::int64_t owner_id() const noexcept
    {
        return m_owner_id;
    }
    std::string text() const noexcept
    {
        return m_text;
    }
    attachment::attachments_t attachments() const noexcept
    {
        return m_attachments;
    }

private:
    std::int64_t m_id;
    std::int64_t m_from_id;
    std::int64_t m_owner_id;
    std::string m_text;
    attachment::attachments_t m_attachments;
};
}// namespace event
}// namespace vk

#endif// VK_WALL_REPOST_H
