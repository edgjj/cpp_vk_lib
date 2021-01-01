#pragma once

#include "vkapi/include/methods/messages.hpp"
#include "vkapi/include/methods/photos.hpp"

#include "bot/commands/base_command.hpp"

class search_pics_command : public base_command
{
public:
  void execute(const vk::event::message_new& event) const override
  {
    auto photos_list = _photos.search(event.text(), 100);

    if (photos_list.empty())
    {
      _messages.send(event.peer_id(), "No photos found");
    }
    else
    {
      _messages.send(event.peer_id(), "", photos_list);
    }
}

private:
    vk::messages _messages;
    vk::photos _photos;
};
