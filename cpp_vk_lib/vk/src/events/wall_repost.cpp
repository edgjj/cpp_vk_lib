#include "vk/include/events/wall_repost.hpp"

#include "spdlog/spdlog.h"

namespace vk::event {

wall_repost::wall_repost(int64_t id, int64_t from_id, int64_t owner_id, std::string text)
    : id_(id)
    , from_id_(from_id)
    , owner_id_(owner_id)
    , text_(std::move(text))
    , attachments_()
{
    spdlog::trace("create wall_repost");
    spdlog::trace("\tid           {}", id_);
    spdlog::trace("\tfrom_id      {}", from_id_);
    spdlog::trace("\towner_id     {}", owner_id_);
    spdlog::trace("\ttext         {}", text_);
    spdlog::trace("\tattachments: {}", attachments_.size());
}

void wall_repost::construct_attachments(std::vector<vk::attachment::attachment_ptr_t>&& attachments)
{
    attachments_ = std::move(attachments);
}

int64_t wall_repost::id() const noexcept
{
    return id_;
}

int64_t wall_repost::from_id() const noexcept
{
    return from_id_;
}

int64_t wall_repost::owner_id() const noexcept
{
    return owner_id_;
}

const std::string& wall_repost::text() const noexcept
{
    return text_;
}

const std::vector<vk::attachment::attachment_ptr_t>& wall_repost::attachments() const noexcept
{
    return attachments_;
}

}// namespace vk::event