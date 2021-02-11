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
        for (auto&& command : commands)
            logger(logflag::debug | logflag::green) << "loaded command: " << command.first;
        logger(logflag::debug | logflag::green) << "total commands: " << commands.size();
    }
private:
    std::unordered_map<std::string_view, event_wrapper> commands;
};

class long_poller {
public:
    explicit long_poller() : data(api.server()) { }
    using message_event_wrapper = std::function<void(const vk::event::message_new&)>;
    void on_message_event(std::string_view trigger, message_event_wrapper function) {
        handler.on_command(trigger, function);
    }
    void loop() {
        while (true) {
            auto events = api.listen(data);
            std::for_each(events.begin(), events.end(), [this](auto& event){
                if (event->on_type("message_new")) {
                    api.queue([this, e = event->get_message_event()]{
                        handler.try_execute(e.text(), e);
                    });
                }
                data.ts = event->ts();
            });
            api.run();
        }
    }
private:
    message_new_handler handler;
    vk::long_poll_api api;
    vk::long_poll_data data;
};

int main() {
    long_poller poller;
    vk::messages messages;
    poller.on_message_event("text", [&messages](const vk::event::message_new& event){
        messages.send(event.peer_id(), vk::string_util::format("Message: {}.", event.text()));
    });
    poller.loop();
    return 0;
}
