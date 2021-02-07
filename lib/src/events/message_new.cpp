#include "simdjson.h"

#include "events/message_new.hpp"


vk::event::message_new::message_new(std::int64_t peer_id, std::int64_t from_id, std::string_view text, std::string_view raw_json, const simdjson::dom::array& attachments)
{
    this->_peer_id  = peer_id;
    this->_from_id  = from_id;
    this->_text     = text;
    this->_raw_json = raw_json;

    try_get_attachments(attachments);
}

vk::event::message_new::message_new(std::string_view raw_json)
{
    simdjson::dom::parser parser;
    simdjson::dom::object message = parser.parse(raw_json)["object"]["message"];

    _raw_json  = raw_json;
    _from_id   = message["from_id"].get_int64();
    _peer_id   = message["peer_id"].get_int64();
    _text      = message["text"].get_c_str();

    if (message["reply_message"].is_object())
        try_get_reply(message["reply_message"].get_object());

    if (message["attachments"].is_array())
        try_get_attachments(message["attachments"].get_array());

    if (message["fwd_messages"].get_array().size() != 0)
        try_get_fwd_messages(message["fwd_messages"].get_array());
}

void vk::event::message_new::try_get_fwd_messages(const simdjson::dom::array& messages)
{
    for (const simdjson::dom::element& fwd_message : messages)
    {
        _fwd_messages.push_back(
            std::make_shared<message_new>(
                fwd_message["peer_id"].get_int64(),
                fwd_message["from_id"].get_int64(),
                fwd_message["text"].get_string(),
                simdjson::to_string(fwd_message),
                fwd_message["attachments"].get_array()
            )
        );
    }
    _has_fwd_messages = true;
}

void vk::event::message_new::try_get_reply(const simdjson::dom::object& object)
{
    _reply = std::make_shared<message_new>(
        object["peer_id"].get_int64(),
        object["from_id"].get_int64(),
        object["text"].get_string(),
        simdjson::to_string(object),
        object["attachments"].get_array()
    );
    _has_reply = true;
}

static std::shared_ptr<vk::attachment::photo_attachment> get_photo(const simdjson::dom::element& attachment)
{
    return std::make_shared<vk::attachment::photo_attachment>(
        attachment["photo"]["id"].get_int64(),
        attachment["photo"]["owner_id"].get_int64()
    );
}

static std::shared_ptr<vk::attachment::video_attachment> get_video(const simdjson::dom::element& attachment)
{
    return std::make_shared<vk::attachment::video_attachment>(
        attachment["video"]["id"].get_int64(),
        attachment["video"]["owner_id"].get_int64()
    );
}

static std::shared_ptr<vk::attachment::document_attachment> get_doc(const simdjson::dom::element& attachment)
{
    return std::make_shared<vk::attachment::document_attachment>(
        attachment["doc"]["id"].get_int64(),
        attachment["doc"]["owner_id"].get_int64(),
        attachment["doc"]["url"].get_string()
    );
}

static std::shared_ptr<vk::attachment::audio_attachment> get_audio(const simdjson::dom::element& attachment)
{
    return std::make_shared<vk::attachment::audio_attachment>(
       attachment["audio"]["id"].get_int64(),
       attachment["audio"]["owner_id"].get_int64()
    );
}

static std::shared_ptr<vk::attachment::audio_message_attachment> get_audio_message(const simdjson::dom::element& attachment)
{
    return std::make_shared<vk::attachment::audio_message_attachment>(
        attachment["audio_message"]["id"].get_int64(),
        attachment["audio_message"]["owner_id"].get_int64(),
        attachment["audio_message"]["link_ogg"].get_string(),
        attachment["audio_message"]["link_mp3"].get_string()
    );
}

static std::shared_ptr<vk::attachment::wall_attachment> get_wall(const simdjson::dom::element& attachment)
{
    return std::make_shared<vk::attachment::wall_attachment>(
        attachment["wall"]["from_id"].get_int64(),
        attachment["wall"]["id"].get_int64()
    );
}

void vk::event::message_new::try_get_attachments(const simdjson::dom::array& attachments)
{
    for (const simdjson::dom::element& attachment : attachments)
    {
        std::string type = attachment["type"].get_string().take_value().data();
        if (type == "photo")        { _attachments.push_back(get_photo(attachment)); }
        if (type == "video")        { _attachments.push_back(get_video(attachment)); }
        if (type == "doc")          { _attachments.push_back(get_doc(attachment)); }
        if (type == "audio")        { _attachments.push_back(get_audio(attachment)); }
        if (type == "wall")         { _attachments.push_back(get_wall(attachment)); }
        if (type == "audio_message") { _attachments.push_back(get_audio_message(attachment)); }
    }
}

vk::attachment::attachments_t vk::event::message_new::attachments() const noexcept
{
    return _attachments;
}

std::string vk::event::message_new::text() const noexcept
{
    return _text;
}

std::int64_t vk::event::message_new::from_id() const noexcept
{
    return _from_id;
}

std::int64_t vk::event::message_new::peer_id() const noexcept
{
    return _peer_id;
}

bool vk::event::message_new::has_reply() const noexcept
{
    return _has_reply;
}

bool vk::event::message_new::has_fwd_messages() const noexcept
{
    return _has_fwd_messages;
}

std::string vk::event::message_new::dump() const noexcept
{
    return _raw_json;
}

std::vector<std::shared_ptr<vk::event::message_new>> vk::event::message_new::fwd_messages() const
{
    if (_has_fwd_messages) return _fwd_messages;
    else throw std::runtime_error("Attempting accessing empty forward message list");
}

vk::event::message_new vk::event::message_new::reply() const
{
    if (_has_reply) return *_reply;
    else throw std::runtime_error("Attempting accessing empty reply");
}
