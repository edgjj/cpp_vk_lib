#ifndef BOT_COMMANDS_DOWNLOAD_VOICE_MESSAGE_COMMAND_HPP
#define BOT_COMMANDS_DOWNLOAD_VOICE_MESSAGE_COMMAND_HPP

#include "../commands/base.hpp"

#include "cpp_vk_lib/events/message_new.hpp"
#include "cpp_vk_lib/methods/messages.hpp"
#include "cpp_vk_lib/net/network.hpp"

#include <ctime>

namespace bot {
namespace command {

class voice_message_download final : public base
{
public:
    void execute(const vk::event::message_new& event) const override
    {
        for (auto&& attachment : event.reply()->attachments()) {
            if (attachment->type() == "audio_message") {
                m_messages.send(event.peer_id(), "Downloading...");
                auto audio_message = vk::attachment::cast<vk::attachment::audio_message>(attachment);
                std::string path = "/tmp/audio" + std::to_string(std::time(nullptr)) + ".mp3";

                if (vk::network::download(path, audio_message->raw_mp3()) == 0) {
                    m_messages.send(event.peer_id(), "Downloaded");
                } else {
                    m_messages.send(event.peer_id(), "Error while downloading");
                }
            }
        }
    }

private:
    vk::method::messages m_messages{vk::method::messages::disable_mentions};
};

}// namespace command
}// namespace bot

#endif// BOT_COMMANDS_DOWNLOAD_VOICE_MESSAGE_COMMAND_HPP
