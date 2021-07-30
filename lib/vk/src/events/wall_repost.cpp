#include "vk/include/events/wall_repost.hpp"

#include "runtime/include/misc/cppdefs.hpp"

#include "spdlog/spdlog.h"

vk::event::wall_repost::wall_repost(int64_t id, int64_t from_id, int64_t owner_id, std::string text)
    : m_id(id)
    , m_from_id(from_id)
    , m_owner_id(owner_id)
    , m_text(text)
    , m_attachments()
{
    spdlog::info("create wall_repost");
    spdlog::info("\tid           {}", m_id);
    spdlog::info("\tfrom_id      {}", m_from_id);
    spdlog::info("\towner_id     {}", m_owner_id);
    spdlog::info("\ttext         {}", m_text);
    spdlog::info("\tattachments: {}", m_attachments.size());
}

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
