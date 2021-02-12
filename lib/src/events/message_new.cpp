#include "simdjson.h"

#include "events/message_new.hpp"


vk::event::message_new::message_new(std::int64_t peer_id, std::int64_t from_id, std::string_view text, std::string_view raw_json, const simdjson::dom::array& attachments) {
    this->_peer_id  = peer_id;
    this->_from_id  = from_id;
    this->_text     = text;
    this->_raw_json = raw_json;

    _attachments = att_handler.try_get(attachments);
}

vk::event::message_new::message_new(std::string_view raw_json) {
    simdjson::dom::parser parser;
    simdjson::dom::object message = parser.parse(raw_json)["object"]["message"];

    _raw_json  = raw_json;
    _from_id   = message["from_id"].get_int64();
    _peer_id   = message["peer_id"].get_int64();
    _text      = message["text"].get_c_str();

    if (message["reply_message"].is_object())
        try_get_reply(message["reply_message"].get_object());

    if (message["attachments"].is_array())
        _attachments = att_handler.try_get(message["attachments"].get_array());

    if (message["fwd_messages"].get_array().size() != 0)
        try_get_fwd_messages(message["fwd_messages"].get_array());
}

void vk::event::message_new::try_get_fwd_messages(const simdjson::dom::array& messages) {
    for (const simdjson::dom::element& fwd_message : messages) {
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

void vk::event::message_new::try_get_reply(const simdjson::dom::object& object) {
    _reply = std::make_shared<message_new>(
        object["peer_id"].get_int64(),
        object["from_id"].get_int64(),
        object["text"].get_string(),
        simdjson::to_string(object),
        object["attachments"].get_array()
    );
    _has_reply = true;
}

vk::attachment::attachments_t vk::event::message_new::attachments() const noexcept {
    return _attachments;
}
std::string vk::event::message_new::text() const noexcept {
    return _text;
}
std::int64_t vk::event::message_new::from_id() const noexcept {
    return _from_id;
}
std::int64_t vk::event::message_new::peer_id() const noexcept {
    return _peer_id;
}
bool vk::event::message_new::has_reply() const noexcept {
    return _has_reply;
}
bool vk::event::message_new::has_fwd_messages() const noexcept {
    return _has_fwd_messages;
}
std::string vk::event::message_new::dump() const noexcept {
    return _raw_json;
}
std::vector<std::shared_ptr<vk::event::message_new>> vk::event::message_new::fwd_messages() const {
    if (_has_fwd_messages) return _fwd_messages;
    else throw std::runtime_error("Attempting accessing empty forward message list.");
}
vk::event::message_new vk::event::message_new::reply() const {
    if (_has_reply) return *_reply;
    else throw std::runtime_error("Attempting accessing empty reply.");
}
