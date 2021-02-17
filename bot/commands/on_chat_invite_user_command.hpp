#ifndef BOT_ON_CHAT_INVITE_USER_COMMAND_H
#define BOT_ON_CHAT_INVITE_USER_COMMAND_H

#include "events/message_new.hpp"
#include "methods/messages.hpp"
#include "string_util/string_util.hpp"

#include "../commands/base_command.hpp"


class on_chat_invite_user_command final : public base_command {
public:
  void execute(const vk::event::message_new& event) override {
    auto invited_user = vk::action::get_chat_invite_user_action(event.action());
    messages.send(event.peer_id(),
      vk::string_util::format("Hello, {}.", invited_user->member_id()));
  }
private:
  vk::method::messages messages;
};

#endif // BOT_ON_CHAT_INVITE_USER_COMMAND_H
