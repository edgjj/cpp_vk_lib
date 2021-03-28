#include "simdjson.h"

#include "methods/photos.hpp"
#include "exception/error_processor.hpp"


vk::method::photos::photos()
  : parser(std::make_shared<simdjson::dom::parser>())
  , method_util()
  , document()
{ }

vk::method::photos::photos(std::string_view user_token)
  : parser(std::make_shared<simdjson::dom::parser>())
  , method_util(user_token.data())
  , document(user_token.data())
{ }

vk::method::photos::~photos() = default;

vk::attachment::attachments_t vk::method::photos::search(
    std::string_view query,
    std::int64_t count
) const {
  return document.search("photos.search", query, count);
}

std::string vk::method::photos::get_messages_upload_server(std::int64_t peer_id) const {
  return method_util.call("photos.getMessagesUploadServer", method_util.group_args({
    {"peer_id", std::to_string(peer_id)}
  }));
}

std::string vk::method::photos::get_chat_upload_server(
    std::int64_t chat_id,
    std::int64_t crop
) const {
  return method_util.call("photos.getChatUploadServer", method_util.group_args({
    {"crop_x",  std::to_string(crop)},
    {"crop_y",  std::to_string(crop)},
    {"chat_id", std::to_string(chat_id - method_util.chat_id_constant)}
  }));
}

static std::map<std::string, std::string> save_messages_photo_args(
    simdjson::dom::object&& upload_response
) {
  return {
    {"photo",   upload_response["photo"].get_c_str().take_value()},
    {"hash",    upload_response["hash"].get_c_str().take_value()},
    {"server",  std::to_string(upload_response["server"].get_int64())}
  };
}

std::shared_ptr<vk::attachment::photo> vk::method::photos::save_messages_photo(
    std::string_view filename,
    std::string_view raw_server
) const {
  simdjson::dom::object upload_response = document.upload(filename, raw_server, "file");

  if (upload_response["photo"].get_string().take_value() == "[]" ||
      upload_response["photo"].get_string().take_value() == "")
  {
    processing::log_and_throw<exception::upload_error>(
      "photos", upload_response
    );
  }

  std::string raw_vk_response(
    method_util.call("photos.saveMessagesPhoto", method_util.group_args(
      save_messages_photo_args(std::move(upload_response))))
  );

  simdjson::dom::object uploaded(parser->parse(raw_vk_response)["response"].at(0));
  std::int64_t owner_id(uploaded["owner_id"].get_int64());
  std::int64_t id(uploaded["id"].get_int64());

  return std::make_shared<vk::attachment::photo>(owner_id, id);
}
