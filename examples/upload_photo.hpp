#pragma once

#include "vkapi/include/methods/photos.hpp"
#include "vkapi/include/methods/messages.hpp"


void upload_photo_to_private_message(long peer_id, std::string_view path, vk::photos& photos, vk::messages& messages)
{
  std::string raw_json = photos.get_messages_upload_server(peer_id);
  std::shared_ptr<vk::attachment::photo_attachment> attachment = photos.save_messages_photo(path, raw_json);
  messages.send(peer_id, "uploaded attachment: ", { attachment });
}
