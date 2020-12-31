#include <simdjson.h>

#include "vkapi/include/lib/network.hpp"
#include "vkapi/include/methods/audio.hpp"

std::string vk::audio::get_upload_server() const
{
  return network->request(append_url("audio.getUploadServer"), {
    {"access_token",  user_token },
    {"v",             api_v      },
  });
}

void vk::audio::save(std::string_view artist, std::string_view title, std::string_view filename, std::string_view raw_server)
{
  std::string raw_upload_response =
  network->upload("file", filename, static_cast<std::string_view>(parser->parse(raw_server)["response"]["upload_url"]));

  simdjson::dom::object upload_response = parser->parse(raw_upload_response);

  network->request(append_url("audio.save"), {
    { "server",        std::to_string(static_cast<std::int64_t>(upload_response["server"]))},
    { "audio",         static_cast<std::string>(upload_response["audio"])},
    { "hash",          static_cast<std::string>(upload_response["hash"])},
    { "artist",        artist.data()},
    { "title",         title.data()},
    { "access_token",  user_token },
    { "v",             api_v      }
  });
}
