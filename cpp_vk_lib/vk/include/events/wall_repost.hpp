#ifndef VK_EVENTS_WALL_REPOST_HPP
#define VK_EVENTS_WALL_REPOST_HPP

#include "vk/include/attachment/attachment.hpp"

#include <vector>

namespace vk::event {
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

    void construct_attachments(std::vector<vk::attachment::attachment_ptr_t>&& attachments);

    bool has_attachments() const noexcept;
    int64_t id() const noexcept;
    int64_t from_id() const noexcept;
    int64_t owner_id() const noexcept;
    const std::string& text() const noexcept;
    const std::vector<vk::attachment::attachment_ptr_t>& attachments() const noexcept;

private:
    int64_t id_;
    int64_t from_id_;
    int64_t owner_id_;
    std::string text_;
    std::vector<vk::attachment::attachment_ptr_t> attachments_;
};

}// namespace vk::event

std::ostream& operator<<(std::ostream& ostream, const vk::event::wall_repost& event);

#endif// VK_EVENTS_WALL_REPOST_HPP
