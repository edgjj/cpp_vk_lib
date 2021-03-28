#include "cpp_vk_lib/long_poll/api.hpp"
#include "cpp_vk_lib/methods/messages.hpp"

int main() {
  const std::size_t new_server_interval_secs = 5;
  const std::size_t lp_timeout_secs = 60;

  vk::config::load("/home/machen/config.json");
  vk::long_poll::api api(new_server_interval_secs);
  vk::long_poll::data data = api.server();
  vk::method::messages messages(vk::method::messages::disable_mentions);
  while (true) {
    for (auto&& event : api.listen(data, lp_timeout_secs)) {
      api.on_event("message_new", *event, [&event, &messages]{
        auto message_event = event->get_message_event();
        messages.send(message_event.peer_id(), "response");
      });
      api.run();
    }
  }
}











//#include <unordered_map>

//#include "cpp_vk_lib/config/loader.hpp"

////#include "commands/docs_search.hpp"
//#include "commands/download_voice_message.hpp"
//#include "commands/keyboard.hpp"
//#include "commands/hide_keyboard.hpp"
//#include "commands/upload_voice_message.hpp"
//#include "commands/set_chat_photo.hpp"

//#include "events/on_message_pin.hpp"
//#include "events/on_chat_invite_user.hpp"
//#include "long_poller/long_poller.hpp"


//namespace bot {
//// Example bot class.
//// You can add handling other types of events.
//class bot_object {
//public:
//  void setup() {
//    setup_commands();
//    setup_event_reactions();
//  }
//  int run() {
//    return poller.run();
//  }
//private:
//  void setup_commands() {
//    poller.get_message_handler().on_command("download", std::make_unique<command::voice_message_dowload_command>());
//    poller.get_message_handler().on_command("upload", std::make_unique<command::voice_message_upload_command>());
//    poller.get_message_handler().on_command("chatphoto", std::make_unique<command::set_chat_photo_command>());
////    poller.get_message_handler().on_command("doc", std::make_unique<command::docs_search_command>());
//    poller.get_message_handler().on_command("show", std::make_unique<command::keyboard_command>());
//    poller.get_message_handler().on_command("hide", std::make_unique<command::hide_keyboard_command>());
//    // Other commands...
//  }
//  void setup_event_reactions() {
//    poller.get_message_handler().on_message_pin(std::make_unique<event::on_message_pin_event>());
//    poller.get_message_handler().on_chat_invite_user(std::make_unique<event::on_chat_invite_user_event>());
//    // Other event reactions...
//  }
//  long_poller poller;
//};
//} // namespace bot

//int main() {
//  vk::config::load("/home/machen/config.json");
//  bot::bot_object example;
//  example.setup();
//  return example.run();
//}
