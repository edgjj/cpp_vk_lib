#include <algorithm>
#include <unordered_map>

#include "cpp_vk_lib/common.hpp"
#include "../../dependencies/logger/logger.hpp"


class message_new_handler {
public:
    using event_wrapper = std::function<void(const vk::event::message_new&)>;

    void on_command(std::string_view trigger, event_wrapper function) {
        commands.emplace(trigger, function);
    }
    void try_execute(std::string_view trigger, const vk::event::message_new& event) {
        commands.at(trigger)(event);
    }
    void see_contents() {
        for (auto&& command : commands) {
            logger(logflag::debug | logflag::green) << "loaded command: " << command.first;
        }
        logger(logflag::debug | logflag::green) << "total commands: " << commands.size();
    }

private:
    std::unordered_map<std::string_view, event_wrapper> commands;
};

int main() {
    vk::messages messages;
    vk::long_poll_api long_poll;
    vk::long_poll_data long_poll_data = long_poll.server();
    message_new_handler handler;

    handler.on_command("1", [&messages](const vk::event::message_new& event){
        messages.send(event.peer_id(), "command 1", {
            {"attachment", "photo123_123"}
        });
    });
    handler.on_command("2", [&messages](const vk::event::message_new& event){
        messages.send(event.peer_id(), "command 1", {
            {"attachment", "video123_123"}
        });
    });

    while (true) {
        auto events = long_poll.listen(long_poll_data);
        std::for_each(std::begin(events), std::end(events), [&](auto& common_event){
            if (common_event->on_type("message_new")) {
                long_poll.queue([event = common_event->get_message_event(), &handler](){
                    handler.try_execute(event.text(), event);
                });
            }
        });
        long_poll.run();
    }
}
