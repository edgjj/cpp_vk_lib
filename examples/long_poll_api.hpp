#pragma once

#include "vkapi/include/api/long_poll_api.hpp"
#include "vkapi/include/methods/messages.hpp"

void process_updates(vk::long_poll_data& lp_data, vk::long_poll_api& lp_api, vk::messages& messages)
{
  for (const vk::event::common& event : lp_api.listen(lp_data))
  {
    if (event.type() == "message_new")
    {
      messages.send(event.get_message_event().peer_id(), "Received message event!");
    }
    else if (event.type() == "wall_post_new")
    {
      messages.send(event.get_message_event().peer_id(), "Received wall post event!");
    }
    lp_data.ts = event.ts();
  }
}

void long_poll()
{
  vk::long_poll_api lp_api;
  vk::long_poll_data lp_data;
  vk::messages messages;

  lp_data = lp_api.get_server();

  while(true)
  {
    process_updates(lp_data, lp_api, messages);
  }
}
