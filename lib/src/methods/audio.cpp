#include "methods/audio.hpp"
#include "processing/exception.hpp"


std::string vk::audio::get_upload_server() const {
  return call("audio.getUploadServer", user_args({ }));
}

void vk::audio::save(std::string_view artist, std::string_view title, std::string_view filename, std::string_view raw_server) {
  simdjson::dom::object response =
  parser.parse(
    net_client.upload(
      "file",
      filename,
      parser.parse(raw_server)["response"]["upload_url"].get_string()
    )
  );

  if (response.begin().key() == "error")
    vk_throw(exception::upload_error, -1, "Can't upload file. Maybe is not an mp3 track?");

  call("audio.save", user_args({
    {"server",   std::to_string(response["server"].get_int64())},
    {"audio",    std::string(response["audio"].get_c_str())},
    {"hash",     std::string(response["hash"].get_c_str())},
    {"artist",   artist.data()},
    {"title",    title.data()}
  }));
}
