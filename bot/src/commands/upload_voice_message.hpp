#ifndef BOT_UPLOAD_VOICE_MESSAGE_COMMAND_H
#define BOT_UPLOAD_VOICE_MESSAGE_COMMAND_H

#include "../commands/base.hpp"
#include "cpp_vk_lib/events/message_new.hpp"
#include "cpp_vk_lib/methods/docs.hpp"
#include "cpp_vk_lib/methods/messages.hpp"
#include "cpp_vk_lib/net/client.hpp"


namespace bot {
namespace command {

class voice_message_upload final : public base
{
public:
    explicit voice_message_upload()
      : messages(vk::method::messages::disable_mentions)
      , docs()
    {}
    void execute(const vk::event::message_new& event) const override
    {
        std::string raw_upload_json = docs.get_messages_upload_server("audio_message", event.peer_id());
        // You can organize path retreiving in any convenient way.
        auto audio = docs.save_audio_message("/path/to/audio.mp3", raw_upload_json);
        messages.send(event.peer_id(), "Hey, i have uploaded audio!", {audio});
    }

private:
    vk::method::messages messages;
    vk::method::docs docs;
};
}// namespace command
}// namespace bot

#endif// BOT_UPLOAD_VOICE_MESSAGE_COMMAND_H
