#ifndef BOT_COMMANDS_RAW_METHOD_HPP
#define BOT_COMMANDS_RAW_METHOD_HPP

#include "../commands/base.hpp"

#include "cpp_vk_lib/config/loader.hpp"
#include "cpp_vk_lib/events/message_new.hpp"
#include "cpp_vk_lib/methods/utility/constructor.hpp"

namespace bot {
namespace command {

class raw_method final : public base
{
public:
    void execute(const vk::event::message_new& event) const override
    {
        m_group_constructor
            .method("messages.send")
            .param("random_id", "0")
            .param("disable_mentions", "1")
            .param("peer_id", std::to_string(event.peer_id()))
            .param("message", "Hey, I'm was constructed with raw_method class!")
            .perform_request();
    }

private:
    mutable vk::method::group_constructor m_group_constructor;
};

}// namespace command
}// namespace bot

#endif// BOT_COMMANDS_RAW_METHOD_HPP
