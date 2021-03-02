#include "simdjson.h"

#include "string_utils/string_utils.hpp"
#include "processing/error_processor.hpp"
#include "methods/docs.hpp"


vk::method::docs::docs()
  : parser(std::make_unique<simdjson::dom::parser>())
{ }

vk::method::docs::~docs() = default;

vk::attachment::attachments_t vk::method::docs::search(std::string_view query, std::int64_t count) {
  return common_search("docs.search", query, count);
}

void vk::method::docs::edit(
    int64_t owner_id,
    int64_t doc_id,
    std::string_view title,
    std::initializer_list<std::string>&& tags
) {
  simdjson::dom::object response =
  method_util.call_and_parse("docs.edit", method_util.user_args({
    {"owner_id",    std::to_string(owner_id)},
    {"doc_id",      std::to_string(doc_id)},
    {"title",       title.data()},
    {"tags",        string_utils::join<std::string>(std::move(tags)).data()}
  }));

  if (response.begin().key() == "error") {
    processing::error_log_and_throw("messages", exception::access_error(
      response["error"]["error_code"].get_int64(), response["error"]["error_msg"].get_c_str()
    ));
  }
}

void vk::method::docs::remove(int64_t owner_id, int64_t doc_id) {
  simdjson::dom::object response =
  method_util.call_and_parse("docs.delete", method_util.user_args({
    {"owner_id", std::to_string(owner_id)},
    {"doc_id", std::to_string(doc_id)}
  }));

  if (response.begin().key() == "error") {
    processing::error_log_and_throw("messages", exception::access_error(
      response["error"]["error_code"].get_int64(), response["error"]["error_msg"].get_c_str()
    ));
  }
}

std::string vk::method::docs::get_upload_server(std::int64_t group_id) const {
  return method_util.call("docs.getUploadServer", method_util.group_args({
    {"group_id", std::to_string(group_id)}
  }));
}

std::string vk::method::docs::get_wall_upload_server(int64_t group_id) const {
  return method_util.call("docs.getWallUploadServer", method_util.group_args({
    {"group_id", std::to_string(group_id)}
  }));
}

std::string vk::method::docs::get_messages_upload_server(std::string_view type, int64_t peer_id) const {
  return method_util.call("docs.getMessagesUploadServer", method_util.group_args({
    {"peer_id", std::to_string(peer_id)},
    {"type", type.data()}
  }));
}

std::shared_ptr<vk::attachment::audio_message> vk::method::docs::save_audio_message(
    std::string_view filename,
    std::string_view raw_server
) {
  simdjson::dom::object upload_response = common_upload(filename, raw_server, "file");

  if (upload_response.begin().key() != "file") {
    processing::error_log_and_throw("docs", exception::upload_error(
      -1, "Can't upload file. Maybe is not an mp3 track?"));
  }

  std::string file(upload_response["file"].get_c_str());
  if (file == "") { return { }; }
  std::string raw_save_response =
    method_util.call("docs.save", method_util.group_args({{"file", file}, {"title", "voice"}}));

  simdjson::dom::object uploaded_doc = parser->parse(raw_save_response)["response"]["audio_message"];

  return
  std::make_shared<vk::attachment::audio_message>(
    uploaded_doc["owner_id"].get_int64(),
    uploaded_doc["id"].get_int64(),
    uploaded_doc["link_ogg"].get_string(),
    uploaded_doc["link_mp3"].get_string()
  );
}
