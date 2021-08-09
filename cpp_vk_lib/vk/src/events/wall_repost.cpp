#include "vk/include/events/wall_repost.hpp"

#include "runtime/include/misc/cppdefs.hpp"

#include "spdlog/spdlog.h"

vk::event::wall_repost::wall_repost(int64_t id, int64_t from_id, int64_t owner_id, std::string text)
    : id_(id)
    , from_id_(from_id)
    , owner_id_(owner_id)
    , text_(std::move(text))
    , attachments_()
{
    spdlog::info("create wall_repost");
    spdlog::info("\tid           {}", id_);
    spdlog::info("\tfrom_id      {}", from_id_);
    spdlog::info("\towner_id     {}", owner_id_);
    spdlog::info("\ttext         {}", text_);
    spdlog::info("\tattachments: {}", attachments_.size());
}

void vk::event::wall_repost::construct_attachments(std::vector<vk::attachment::attachment_ptr_t>&& attachments)
{
    attachments_ = attachments;
}

int64_t vk::event::wall_repost::id() const noexcept
{
    return id_;
}

int64_t vk::event::wall_repost::from_id() const noexcept
{
    return from_id_;
}

int64_t vk::event::wall_repost::owner_id() const noexcept
{
    return owner_id_;
}

const std::string& vk::event::wall_repost::text() const noexcept
{
    return text_;
}

const std::vector<vk::attachment::attachment_ptr_t>& vk::event::wall_repost::attachments() const noexcept
{
    return attachments_;
}
