#include <simdjson.h>

#include "vkapi/include/updates/message_new.hpp"

vk::update::message_new::message_new(long peer_id, long from_id, std::string_view text)
{
  this->_peer_id = peer_id;
  this->_from_id = from_id;
  this->_text    = text;
}

vk::update::message_new::message_new(std::string_view raw_json)
{
  static simdjson::dom::parser parser;
  simdjson::dom::object object = parser.parse(raw_json)["object"]["message"];

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

void vk::update::message_new::get_reply(const simdjson::dom::object& object)
{
  _reply = new message_new(
    static_cast<long>(object["from_id"]),
    static_cast<long>(object["peer_id"]),
    static_cast<std::string_view>(object["text"])
  );
  _is_reply = true;
}

/// ... Насчёт полезности этого метода ничего сказать не могу.
void vk::update::message_new::get_attachments(const simdjson::dom::array& attachments)
{
  for (const simdjson::dom::object& attachment : attachments)
  {
    std::string type = static_cast<std::string>(attachment["type"]);
    if (type == "photo")
    {
      _attachments.push_back(std::make_shared<attachment::photo_attachment>(
        static_cast<long>(attachment["photo"]["id"]),
        static_cast<long>(attachment["photo"]["owner_id"])));
    }
    if (type == "video")
    {
      _attachments.push_back(std::make_shared<attachment::video_attachment>(
        static_cast<long>(attachment["video"]["id"]),
        static_cast<long>(attachment["video"]["owner_id"])));
    }
    if (type == "doc")
    {
      _attachments.push_back(std::make_shared<attachment::document_attachment>(
        static_cast<long>(attachment["doc"]["id"]),
        static_cast<long>(attachment["doc"]["owner_id"]),
        static_cast<std::string>(attachment["doc"]["url"])));
    }
    if (type == "audio")
    {
      _attachments.push_back(std::make_shared<attachment::audio_attachment>(
        static_cast<long>(attachment["audio"]["id"]),
        static_cast<long>(attachment["audio"]["owner_id"])));
    }
    if (type == "audio_message")
    {
      _attachments.push_back(std::make_shared<attachment::audio_message_attachment>(
        static_cast<long>(attachment["audio_message"]["id"]),
        static_cast<long>(attachment["audio_message"]["owner_id"]),
        static_cast<std::string>(attachment["audio_message"]["link_ogg"]),
        static_cast<std::string>(attachment["audio_message"]["link_mp3"])));
    }
    if (type == "wall")
    {
      _attachments.push_back(std::make_shared<attachment::wall_attachment>(
        static_cast<long>(attachment["wall"]["from_id"]),
        static_cast<long>(attachment["wall"]["id"])));
    }
  }
}

vk::attachment::attachment_list vk::update::message_new::attachments() const noexcept
{
  return _attachments;
}

std::string vk::update::message_new::text() const noexcept
{
  return _text;
}

long vk::update::message_new::from_id() const noexcept
{
  return _from_id;
}

long vk::update::message_new::peer_id() const noexcept
{
  return _peer_id;
}

bool vk::update::message_new::has_reply() const noexcept
{
  return _is_reply;
}

vk::update::message_new vk::update::message_new::reply() const
{
  if (_is_reply) return *_reply;
  else throw std::runtime_error("Attempting accessing empty response");
}
