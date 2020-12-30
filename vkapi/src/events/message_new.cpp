#include <simdjson.h>

#include "vkapi/include/events/message_new.hpp"

vk::event::message_new::message_new(long peer_id, long from_id, std::string_view text, std::string raw_json, const simdjson::dom::array& attachments)
{
  this->_peer_id  = peer_id;
  this->_from_id  = from_id;
  this->_text     = text;
  this->_raw_json = raw_json;

  get_attachments(attachments);
}

vk::event::message_new::message_new(std::string_view raw_json)
{
  static simdjson::dom::parser parser;
  simdjson::dom::object object = parser.parse(raw_json)["object"]["message"];

  _raw_json  = raw_json;
  _from_id   = object["from_id"].get_int64();
  _peer_id   = object["peer_id"].get_int64();
  _text      = object["text"].get_c_str();

  if (object["reply_message"].is_object())
  {
    get_reply(object["reply_message"].get_object());
  }
  if (object["attachments"].is_array())
  {
    get_attachments(object["attachments"].get_array());
  }
}

void vk::event::message_new::get_reply(const simdjson::dom::object& object)
{
  _reply = new message_new(
    static_cast<long>(object["from_id"]),
    static_cast<long>(object["peer_id"]),
    static_cast<std::string_view>(object["text"]),
    simdjson::to_string(object),
    object["attachments"].get_array()
  );
  _is_reply = true;
}

static inline std::shared_ptr<vk::attachment::photo_attachment> get_photo(const simdjson::dom::object& attachment)
{
  return
  std::make_shared<vk::attachment::photo_attachment>(
    static_cast<long>(attachment["photo"]["id"]),
    static_cast<long>(attachment["photo"]["owner_id"])
  );
}

static inline std::shared_ptr<vk::attachment::video_attachment> get_video(const simdjson::dom::object& attachment)
{
  return
  std::make_shared<vk::attachment::video_attachment>(
    static_cast<long>(attachment["video"]["id"]),
    static_cast<long>(attachment["video"]["owner_id"])
  );
}

static inline std::shared_ptr<vk::attachment::document_attachment> get_doc(const simdjson::dom::object& attachment)
{
  return
  std::make_shared<vk::attachment::document_attachment>(
    static_cast<long>(attachment["doc"]["id"]),
    static_cast<long>(attachment["doc"]["owner_id"]),
    static_cast<std::string_view>(attachment["doc"]["url"])
  );
}

static inline std::shared_ptr<vk::attachment::audio_attachment> get_audio(const simdjson::dom::object& attachment)
{
  return
  std::make_shared<vk::attachment::audio_attachment>(
    static_cast<long>(attachment["audio"]["id"]),
    static_cast<long>(attachment["audio"]["owner_id"])
  );
}

static inline std::shared_ptr<vk::attachment::audio_message_attachment> get_audio_message(const simdjson::dom::object& attachment)
{
  return
  std::make_shared<vk::attachment::audio_message_attachment>(
    static_cast<long>(attachment["audio_message"]["id"]),
    static_cast<long>(attachment["audio_message"]["owner_id"]),
    static_cast<std::string_view>(attachment["audio_message"]["link_ogg"]),
    static_cast<std::string_view>(attachment["audio_message"]["link_mp3"]));
}

static inline std::shared_ptr<vk::attachment::wall_attachment> get_wall(const simdjson::dom::object& attachment)
{
  return
  std::make_shared<vk::attachment::wall_attachment>(
    static_cast<long>(attachment["wall"]["from_id"]),
    static_cast<long>(attachment["wall"]["id"])
  );
}

void vk::event::message_new::get_attachments(const simdjson::dom::array& attachments)
{
  for (const simdjson::dom::object& attachment : attachments)
  {
    std::string type = static_cast<std::string>(attachment["type"]);
    if (type == "photo")         _attachments.push_back(get_photo(attachment));
    if (type == "video")         _attachments.push_back(get_video(attachment));
    if (type == "doc")           _attachments.push_back(get_doc(attachment));
    if (type == "audio")         _attachments.push_back(get_audio(attachment));
    if (type == "audio_message") _attachments.push_back(get_audio_message(attachment));
    if (type == "wall")          _attachments.push_back(get_wall(attachment));
  }
}

vk::attachment::attachment_list vk::event::message_new::attachments() const noexcept
{
  return _attachments;
}

std::string vk::event::message_new::text() const noexcept
{
  return _text;
}

long vk::event::message_new::from_id() const noexcept
{
  return _from_id;
}

long vk::event::message_new::peer_id() const noexcept
{
  return _peer_id;
}

bool vk::event::message_new::has_reply() const noexcept
{
  return _is_reply;
}

std::string vk::event::message_new::dump() const noexcept
{
  return _raw_json;
}

vk::event::message_new vk::event::message_new::reply() const
{
  if (_is_reply) return *_reply;
  else throw std::runtime_error("Attempting accessing empty response");
}
