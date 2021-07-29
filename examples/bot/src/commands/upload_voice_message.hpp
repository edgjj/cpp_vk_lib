#ifndef BOT_COMMANDS_UPLOAD_VOICE_MESSAGE_HPP
#define BOT_COMMANDS_UPLOAD_VOICE_MESSAGE_HPP

#include "../commands/base.hpp"

#include "cpp_vk_lib/events/message_new.hpp"
#include "cpp_vk_lib/methods/docs.hpp"
#include "cpp_vk_lib/methods/messages.hpp"
#include "cpp_vk_lib/net/network.hpp"

namespace bot {
namespace command {

class voice_message_upload final : public base
{
public:
    explicit voice_message_upload()
      : m_messages(vk::method::messages::disable_mentions)
      , m_docs() {}

    void execute(const vk::event::message_new& event) const override
    {
        std::string raw_upload_json = m_docs.get_messages_upload_server("audio_message", event.peer_id());
        // You can organize path retrieving in any convenient way.
        auto audio = m_docs.save_audio_message("/path/to/audio.mp3", raw_upload_json);
        m_messages.send(event.peer_id(), "Hey, i have uploaded audio!", {audio});
    }

private:
    vk::method::messages m_messages;
    vk::method::docs m_docs;
};

}// namespace command
}// namespace bot

#endif// BOT_COMMANDS_UPLOAD_VOICE_MESSAGE_HPP
