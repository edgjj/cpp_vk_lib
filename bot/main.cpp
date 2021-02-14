#include <unordered_map>

#include "commands/docs_search_command.hpp"
#include "commands/on_message_pin_command.hpp"
#include "commands/on_chat_invite_user_command.hpp"
#include "long_poller/long_poller.hpp"


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
        // Other commands...
    }
    void setup_event_reactions() {
        poller.get_message_handler().on_message_pin(std::make_unique<on_message_pin_command>());
        poller.get_message_handler().on_chat_invite_user(std::make_unique<on_chat_invite_user_command>());
        // Other event reaactions...
    }
    long_poller poller;
};

int main() {
    bot example;
    example.setup();
    return example.run();
}
