#ifndef BOT_HANDLERS_MESSAGE_HANDLER_HPP
#define BOT_HANDLERS_MESSAGE_HANDLER_HPP

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

        if (!event.has_action()) {
            m_commands.at(string_util::get_first(event.text()))->execute(event);
            return;
        }

        if (event.on_action("chat_pin_message")) {
            m_message_pin_command->execute(event);
        }

        if (event.on_action("chat_invite_user")) {
            m_chat_invite_user_command->execute(event);
        }
    }

    template <typename Handler>
    message_handler& on_command(std::string_view trigger)
    {
        m_commands.emplace(trigger, std::make_unique<Handler>());
        return *this;
    }

    template <typename Handler>
    message_handler& on_message_pin()
    {
        m_message_pin_command = std::make_unique<Handler>();
        return *this;
    }

    template <typename Handler>
    message_handler& on_chat_invite_user()
    {
        m_chat_invite_user_command = std::make_unique<Handler>();
        return *this;
    }

private:
    std::unordered_map<std::string, std::shared_ptr<command::base>> m_commands{};
    // Event wrappers.
    std::unique_ptr<event::on_message_pin_event> m_message_pin_command{};
    std::unique_ptr<event::on_chat_invite_user_event> m_chat_invite_user_command{};
};

}// namespace bot

#endif// BOT_HANDLERS_MESSAGE_HANDLER_HPP
