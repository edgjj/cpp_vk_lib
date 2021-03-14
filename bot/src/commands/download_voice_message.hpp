#ifndef BOT_DOWNLOAD_VOICE_MESSAGE_COMMAND_H
#define BOT_DOWNLOAD_VOICE_MESSAGE_COMMAND_H

#include "cpp_vk_lib/events/message_new.hpp"
#include "cpp_vk_lib/methods/messages.hpp"
#include "cpp_vk_lib/net/client.hpp"

#include "../commands/base.hpp"


namespace bot {
namespace command {

class voice_message_dowload_command final : public base_command {
public:
  void execute (const vk::event::message_new& event) const override {
    auto reply_message = event.reply();
    for (auto&& attachment : reply_message->attachments()) {
      if (attachment->type() == "audio_message") {
        auto audio_message = vk::attachment::static_cast_to<vk::attachment::audio_message>(attachment);
          messages.send(event.peer_id(), "Downloading...");
          (client.download("voice.mp3", audio_message->raw_mp3()) == 0)
            ? messages.send(event.peer_id(), "Downloaded")
            : messages.send(event.peer_id(), "Error while downloading");
      }
    }
  }
private:
  vk::network_client client;
  vk::method::messages messages{vk::method::messages::disable_mentions};
};
} // namespace command
} // namespace bot

#endif // BOT_DOWNLOAD_VOICE_MESSAGE_COMMAND_H
