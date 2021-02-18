#include "simdjson.h"

#include "methods/audio.hpp"
#include "processing/exception.hpp"


vk::method::audio::audio()
  : parser(std::make_unique<simdjson::dom::parser>())
{ }

vk::method::audio::~audio() = default;

std::string vk::method::audio::get_upload_server() const {
  return method_util.call("audio.getUploadServer", method_util.user_args({ }));
}

void vk::method::audio::save(std::string_view artist, std::string_view title, std::string_view filename, std::string_view raw_server) {
  simdjson::dom::object response =
  parser->parse(
    net_client.upload(
      "file",
      filename,
      parser->parse(raw_server)["response"]["upload_url"].get_string()
    )
  );

  if (response.begin().key() == "error")
    vk_throw(exception::upload_error, -1, "Can't upload file. Maybe is not an mp3 track?");

  method_util.call("audio.save", method_util.user_args({
    {"server",   std::to_string(response["server"].get_int64())},
    {"audio",    std::string(response["audio"].get_c_str())},
    {"hash",     std::string(response["hash"].get_c_str())},
    {"artist",   artist.data()},
    {"title",    title.data()}
  }));
}
