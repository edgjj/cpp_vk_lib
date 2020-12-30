#pragma once

#include "vkapi/include/methods/photos.hpp"
#include "vkapi/include/methods/messages.hpp"


void upload_main_chat_photo(long peer_id, std::string_view path, vk::photos& photos, vk::messages& messages)
{
  std::string raw_json = photos.get_chat_upload_server(peer_id);
  messages.set_chat_photo(path, raw_json);
}
