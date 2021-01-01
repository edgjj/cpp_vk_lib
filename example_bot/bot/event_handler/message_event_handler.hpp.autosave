#pragma once

#include <unordered_map>

#include "bot/3rd_party/logger.hpp"

#include "bot/commands/download_audio_message_command.hpp"
#include "bot/commands/search_pics_command.hpp"

class message_event_handler
{
public:
  explicit
  message_event_handler()
  {
    _command_collection.emplace("pic", std::make_unique<search_pics_command>());
    _command_collection.emplace("voice", std::make_unique<download_audio_message_command>());
  }
  void process(const vk::event::message_new& event)
  {
    std::string trigger = event.text().substr(0, event.text().find(' '));

    if (_command_collection.find(trigger) != _command_collection.end())
    {
        _command_collection[trigger]->execute(event);
        _logger.log(event.text());
    }
  }

private:
  vk::messages _messages;
  std::unordered_map<std::string_view, std::unique_ptr<base_command>> _command_collection;

  vk::third_party::logger _logger { "/path/to/your/logfile" };
};
