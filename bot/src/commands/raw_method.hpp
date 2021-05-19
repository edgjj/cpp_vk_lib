#ifndef BOT_RAW_METHOD_HPP
#define BOT_RAW_METHOD_HPP

#include "../commands/base.hpp"
#include "cpp_vk_lib/config/loader.hpp"
#include "cpp_vk_lib/events/message_new.hpp"
#include "cpp_vk_lib/methods/utility/raw_method.hpp"

namespace bot {
namespace command {

class raw_method final : public base
{
public:
    void execute(const vk::event::message_new& event) const override
    {
        m_raw_method.method("messages.send")
            .param("random_id", "0")
            .param("disable_mentions", "1")
            .param("peer_id", std::to_string(event.peer_id()))
            .param("message", "Hey, I'm was constructed with raw_method class!")
            .param("access_token", vk::config::access_token())
            .param("v", "5.130");
        m_raw_method.execute();
        m_raw_method.reset();
    }

private:
    mutable vk::method::raw_method m_raw_method{vk::method::raw_method::use_api_link};
};

}// namespace command
}// namespace bot

#endif// BOT_RAW_METHOD_HPP
