#ifndef BOT_ON_CHAT_INVITE_USER_EVENT_H
#define BOT_ON_CHAT_INVITE_USER_EVENT_H

#include "cpp_vk_lib/events/message_new.hpp"
#include "cpp_vk_lib/methods/messages.hpp"
#include "cpp_vk_lib/string_utils/string_utils.hpp"


namespace bot {
namespace event {

class on_chat_invite_user_event {
public:
  void execute(const vk::event::message_new& event) const {
    auto invited_user = std::get<vk::action::chat_invite_user>(event.action());
    messages.send(event.peer_id(),
      vk::string_utils::format("Hello, {}.", invited_user.member_id));
  }
private:
  vk::method::messages messages{vk::method::messages::disable_mentions};
};

} // namespace event
} // namespace bot

#endif // BOT_ON_CHAT_INVITE_USER_EVENT_H
