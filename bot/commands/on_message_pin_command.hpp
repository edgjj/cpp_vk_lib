#ifndef BOT_ON_MESSAGE_PIN_COMMAND_H
#define BOT_ON_MESSAGE_PIN_COMMAND_H

#include "events/message_new.hpp"
#include "methods/messages.hpp"
#include "string_util/string_util.hpp"

#include "../commands/base_command.hpp"


class on_message_pin_command final : public base_command {
public:
    void execute(const vk::event::message_new& event) override {
        auto pinned = vk::action::get_chat_pin_message_action(event.action());
        messages.send(event.peer_id(),
            vk::string_util::format("Message was pinned with text: {}.", pinned->message()));
    }
private:
    vk::messages messages;
};

#endif // BOT_ON_MESSAGE_PIN_COMMAND_H
