#pragma once

#include "vkapi/include/methods/messages.hpp"
#include "vkapi/include/methods/docs.hpp"

void upload_audio_message_to_dialog(vk::docs& docs, vk::messages& messages, std::int64_t peer_id, std::string_view filename)
{
  std::string raw_json = docs.get_messages_upload_server("audio_message", peer_id);

  std::shared_ptr<vk::attachment::audio_message_attachment> audio
  = docs.save_audio_message(filename, raw_json);

  messages.send(peer_id, "", { audio });
}
