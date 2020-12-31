#pragma once

#include "commands/base_command.hpp"
#include "vkapi/include/lib/network.hpp"
#include "vkapi/include/methods/messages.hpp"

class download_audio_message_command : public base_command
{
public:
  void execute(const vk::event::message_new& event) const override
  {
    if (not event.has_reply())
    {
      _messages.send(event.peer_id(), "Please, resend audio message");
      return;
    }

    for (auto&& attachment : event.reply().attachments())
    {
      if (attachment->type() == "audio_message")
      {
        auto audio_message = vk::attachment::audio_message_cast(attachment);

        _messages.send(event.peer_id(), "downloading...");
        (_network.download("/home/machen/voice.mp3", audio_message->raw_mp3()) == 0)
          ? _messages.send(event.peer_id(), "downloaded")
          : _messages.send(event.peer_id(), "error");

        break;
      }
    }
  }

private:
    vk::messages _messages;
    vk::lib::network _network;
};
