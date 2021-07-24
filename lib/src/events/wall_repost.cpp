#include "events/wall_repost.hpp"

vk::event::wall_repost::wall_repost(int64_t id, int64_t from_id, int64_t owner_id, std::string text)
    : m_id(id)
    , m_from_id(from_id)
    , m_owner_id(owner_id)
    , m_text(text)
    , m_attachments() {}

void vk::event::wall_repost::construct_attachments(attachment::attachments_t&& attachments)
{
    m_attachments = attachments;
}

int64_t vk::event::wall_repost::id() const noexcept
{
    return m_id;
}

int64_t vk::event::wall_repost::from_id() const noexcept
{
    return m_from_id;
}

int64_t vk::event::wall_repost::owner_id() const noexcept
{
    return m_owner_id;
}

const std::string& vk::event::wall_repost::text() const noexcept
{
    return m_text;
}

const vk::attachment::attachments_t& vk::event::wall_repost::attachments() const noexcept
{
    return m_attachments;
}
