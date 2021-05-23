#ifndef BOT_MESSAGE_HANDLER_H
#define BOT_MESSAGE_HANDLER_H

#include "../commands/base.hpp"
#include "../events/on_chat_invite_user.hpp"
#include "../events/on_message_pin.hpp"
#include "../utils/string_utils.hpp"
#include "spdlog/spdlog.h"

#include <memory>
#include <unordered_map>

namespace bot {

class message_handler
{
public:
    void process(vk::event::message_new&& event) const
    {
        spdlog::info("Message event: {} from {}", event.text(), event.peer_id());
        if (!event.has_action())
        {
            m_commands.at(string_util::get_first(event.text()))->execute(event);
            return;
        }
        if (event.on_action("chat_pin_message"))
        {
            m_message_pin_command->execute(event);
        }
        if (event.on_action("chat_invite_user"))
        {
            m_chat_invite_user_command->execute(event);
        }
    }

    message_handler& on_command(std::string_view trigger, std::shared_ptr<command::base>&& command)
    {
        m_commands.emplace(trigger, std::move(command));
        return *this;
    }
    // Event reactions initializers.
    void on_message_pin(std::unique_ptr<event::on_message_pin_event>&& command)
    {
        m_message_pin_command = std::move(command);
    }

    void on_chat_invite_user(std::unique_ptr<event::on_chat_invite_user_event>&& command)
    {
        m_chat_invite_user_command = std::move(command);
    }

private:
    std::unordered_map<std::string, std::shared_ptr<command::base>> m_commands{};
    // Event wrappers.
    std::unique_ptr<event::on_message_pin_event> m_message_pin_command{};
    std::unique_ptr<event::on_chat_invite_user_event> m_chat_invite_user_command{};
};

}// namespace bot

#endif// BOT_MESSAGE_HANDLER_H
