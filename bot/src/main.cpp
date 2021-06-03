#include "commands/docs_search.hpp"
#include "commands/download_voice_message.hpp"
#include "commands/hide_keyboard.hpp"
#include "commands/keyboard.hpp"
#include "commands/raw_method.hpp"
#include "commands/set_chat_photo.hpp"
#include "commands/upload_voice_message.hpp"
#include "cpp_vk_lib/config/loader.hpp"
#include "events/on_chat_invite_user.hpp"
#include "events/on_message_pin.hpp"
#include "long_poller/long_poller.hpp"


namespace bot {
// Example bot class.
// You can add handling other types of events.
class bot_object
{
public:
    explicit bot_object()
    {
        setup_commands();
        setup_event_reactions();
    }
    int run()
    {
        return poller.run();
    }

private:
    void setup_commands()
    {
        poller.get_message_handler()
            .on_command("/download", std::make_unique<command::voice_message_download>())
            .on_command("/upload", std::make_unique<command::voice_message_upload>())
            .on_command("/chat_photo", std::make_unique<command::set_chat_photo>())
            .on_command("/doc", std::make_unique<command::docs_search>())
            .on_command("/show", std::make_unique<command::keyboard>())
            .on_command("/hide", std::make_unique<command::hide_keyboard>())
            .on_command("/raw", std::make_unique<command::raw_method>());
        // Other commands...
    }

    void setup_event_reactions()
    {
        poller.get_message_handler().on_message_pin(std::make_unique<event::on_message_pin_event>());
        poller.get_message_handler().on_chat_invite_user(std::make_unique<event::on_chat_invite_user_event>());
        // Other event reactions...
    }

    long_poller poller{};
};
}// namespace bot

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Program requires path to config as the only argument." << std::endl;
        exit(-1);
    }
    vk::config::load(argv[1]);
    spdlog::info("Maximum num of workers: {}", vk::config::num_workers());

    bot::bot_object example;
    return example.run();
}
