#pragma once

#include <unordered_map>

#include "commands/command1.hpp"
#include "commands/command2.hpp"

#include "vkapi/include/events/message_new.hpp"
#include "vkapi/include/methods/messages.hpp"

class message_event_handler
{
public:
  explicit
  message_event_handler()
  {
    command_collection.emplace("trigger1", std::make_unique<first_command>());
    command_collection.emplace("trigger2", std::make_unique<second_command>());
  }
  void process(const vk::event::message_new& event)
  {
    std::string trigger = event.text();

    if (command_collection.find(trigger) != command_collection.end())
    {
      _messages.send(event.peer_id(), command_collection[trigger]->execute(trigger));
    }
  }

private:
  vk::messages _messages;
  std::unordered_map<std::string_view, std::unique_ptr<base_command>> command_collection;
};
