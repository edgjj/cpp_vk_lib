#include "simdjson.h"

#include "methods/audio.hpp"
#include "exception/error_processor.hpp"


vk::method::audio::audio()
  : parser(std::make_unique<simdjson::dom::parser>())
  , document()
  , method_util()
{ }

vk::method::audio::~audio() = default;

std::string vk::method::audio::get_upload_server() const {
  return method_util.call("audio.getUploadServer", method_util.user_args({ }));
}

void vk::method::audio::save(
    std::string_view artist,
    std::string_view title,
    std::string_view filename,
    std::string_view raw_server
) const {
  simdjson::dom::object response =
    document.upload(filename, raw_server, "file");

  if (response.begin().key() == "error") {
    processing::log_and_throw<exception::upload_error>(
      "audio", "Can't upload file. Maybe is not an mp3 track?"
    );
  }

  method_util.call("audio.save", method_util.user_args({
    {"server",   std::to_string(response["server"].get_int64())},
    {"audio",    std::string(response["audio"].get_c_str())},
    {"hash",     std::string(response["hash"].get_c_str())},
    {"artist",   artist.data()},
    {"title",    title.data()}
  }));
}
