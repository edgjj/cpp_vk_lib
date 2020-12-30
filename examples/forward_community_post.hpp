#pragma once

#include "vkapi/include/methods/messages.hpp"
#include "vkapi/include/events/common_event.hpp"


void forward_community_post(long peer_id, const vk::event::common& update, vk::messages& messages)
{
  vk::event::wall_post_new wall_post = update.get_wall_post_event();

  auto attachment =
  std::make_shared<vk::attachment::wall_attachment>(
    wall_post.from_id(),
    wall_post.id()
  );

  messages.send(peer_id, "post: ", { attachment });
}
