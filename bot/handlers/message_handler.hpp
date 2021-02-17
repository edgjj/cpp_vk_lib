#ifndef BOT_MESSAGE_HANDLER_H
#define BOT_MESSAGE_HANDLER_H

#include <functional>
#include <unordered_map>
#include <iostream>

#include "events/message_new.hpp"
#include "../commands/base_command.hpp"
#include "../utils/string_utils.hpp"

// Class to handle needed events.
// Analogically, you can create classes for other event types.
class message_handler {
public:
  void process(vk::event::message_new&& event) {
    if (!event.has_action()) {
      commands.at(event.text())->execute(std::move(event));
    } else {
      if (event.on_action("chat_pin_message")) {
        message_pin_command->execute(event);
      }
      if (event.on_action("chat_unpin_message")) {
        message_unpin_command->execute(event);
      }
      if (event.on_action("chat_photo_update")) {
        chat_photo_update_command->execute(event);
      }
      if (event.on_action("chat_invite_user")) {
        chat_invite_user_command->execute(event);
      }
    }
  }

  void on_message_pin(std::unique_ptr<base_command>&& command) {
    message_pin_command = std::move(command);
  }
  void on_message_unpin(std::unique_ptr<base_command>&& command) {
    message_unpin_command = std::move(command);
  }
  void on_chat_photo_update(std::unique_ptr<base_command>&& command) {
    chat_photo_update_command = std::move(command);
  }
  void on_chat_invite_user(std::unique_ptr<base_command>&& command) {
    chat_invite_user_command = std::move(command);
  }
  void on_command(std::string_view trigger, std::shared_ptr<base_command>&& command) {
    commands.emplace(trigger, std::move(command));
  }
private:
  std::unordered_map<std::string, std::shared_ptr<base_command>> commands;

  std::unique_ptr<base_command> message_pin_command;
  std::unique_ptr<base_command> message_unpin_command;
  std::unique_ptr<base_command> chat_photo_update_command;
  std::unique_ptr<base_command> chat_invite_user_command;
};

#endif // BOT_MESSAGE_HANDLER_H
