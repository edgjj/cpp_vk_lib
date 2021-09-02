#ifndef VK_EVENTS_TYPE_HPP
#define VK_EVENTS_TYPE_HPP

namespace vk::event {

enum struct type : unsigned char
{
    message_new,
    wall_post_new,
    wall_reply_new,
    wall_repost
};

}// namespace vk::event

#endif //VK_EVENTS_TYPE_HPP
