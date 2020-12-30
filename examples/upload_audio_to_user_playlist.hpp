#pragma once

#include "vkapi/include/methods/audio.hpp"


void upload_audio_to_user_playlist(std::string_view artist, std::string_view name, std::string_view path, vk::audio& audio)
{
  std::string raw_json = audio.get_upload_server();
  audio.save(artist, name, path, raw_json);
}
