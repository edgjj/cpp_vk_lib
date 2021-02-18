#include <unordered_map>

#include "commands/docs_search_command.hpp"
#include "commands/keyboard_command.hpp"
#include "commands/hide_keyboard_command.hpp"
#include "commands/on_message_pin_command.hpp"
#include "commands/on_chat_invite_user_command.hpp"
#include "long_poller/long_poller.hpp"

// Example bot class.
// You can add handling other types of events.
class bot {
public:
  void setup() {
    setup_commands();
    setup_event_reactions();
  }
  int run() {
    return poller.run();
  }
private:
  void setup_commands() {
    poller.get_message_handler().on_command("doc", std::make_unique<docs_search_command>());
    poller.get_message_handler().on_command("show", std::make_unique<keyboard_command>());
    poller.get_message_handler().on_command("hide", std::make_unique<hide_keyboard_command>());
    // Other commands...
  }
  void setup_event_reactions() {
    poller.get_message_handler().on_message_pin(std::make_unique<on_message_pin_command>());
    poller.get_message_handler().on_chat_invite_user(std::make_unique<on_chat_invite_user_command>());
    // Other event reactions...
  }
  long_poller poller;
};

int main() {
  [[maybe_unused]] vk::config::loader* l = vk::config::load("/home/machen/config.json");
  bot example;
  example.setup();
  return example.run();
}
