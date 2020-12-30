#pragma once

#include "vkapi/include/lib/network.hpp"

#include "vkapi/include/events/message_new.hpp"
#include "vkapi/include/methods/messages.hpp"
#include "vkapi/include/attachment/attachment.hpp"


void download_voice_message(std::string_view path, const vk::event::message_new& message_event, vk::messages& messages)
{
  vk::lib::network network;
  for (auto&& attachment : message_event.attachments())
  {
    if (attachment->type() == "audio_message")
    {
      auto audio_message = vk::attachment::audio_message_cast(attachment);

      messages.send(message_event.peer_id(), "downloading...");
      (network.download(path, audio_message->raw_mp3()) == 0)
        ? messages.send(message_event.peer_id(), "downloaded")
        : messages.send(message_event.peer_id(), "error");
    }
  }
}
