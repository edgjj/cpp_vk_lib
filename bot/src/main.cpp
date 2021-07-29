#include "commands/docs_search.hpp"
#include "commands/download_voice_message.hpp"
#include "commands/hide_keyboard.hpp"
#include "commands/keyboard.hpp"
#include "commands/raw_method.hpp"
#include "commands/set_chat_photo.hpp"
#include "commands/upload_voice_message.hpp"
#include "events/on_chat_invite_user.hpp"
#include "events/on_message_pin.hpp"
#include "long_poller/long_poller.hpp"

#include "cpp_vk_lib/config/loader.hpp"
#include "cpp_vk_lib/log_level.hpp"

namespace bot {
// Example bot class.
// You can add handling other types of events.
class host
{
public:
    host()
    {
        setup_commands();
        setup_event_reactions();

        poller.get_message_handler().dump_commands();
    }

    int run() { return poller.run(); }

private:
    void setup_commands()
    {
        poller.get_message_handler()
            .on_command<command::voice_message_download>("/download")
            .on_command<command::voice_message_upload>("/upload")
            .on_command<command::set_chat_photo>("/chat_photo")
            .on_command<command::docs_search>("/doc")
            .on_command<command::keyboard>("/show")
            .on_command<command::hide_keyboard>("/hide")
            .on_command<command::raw_method>("/raw");
        // Other commands...
    }

    void setup_event_reactions()
    {
        poller.get_message_handler()
            .on_message_pin<event::on_message_pin_event>()
            .on_chat_invite_user<event::on_chat_invite_user_event>();
        // Other event reactions...
    }

    long_poller poller{};
};

}// namespace bot

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Program requires path to config as the only argument." << std::endl;
        exit(-1);
    }

    vk::config::load(argv[1]);
    vk::log_level::trace();

//    auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
//    auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
//        /*base_filename=*/vk::config::log_path(),
//        /*max_size=*/1024*1024,
//        /*max_files=*/1,
//        /*rotate_on_open=*/false);

//    std::vector<spdlog::sink_ptr> sinks {stdout_sink, rotating_sink};

//    auto logger = std::make_shared<spdlog::logger>(
//        "vk",
//        sinks.begin(),
//        sinks.end()
//    );

//    spdlog::register_logger(logger);
//    spdlog::set_default_logger(logger);

    spdlog::info("workers: {}", vk::config::num_workers());

    bot::host example;
    return example.run();
}
