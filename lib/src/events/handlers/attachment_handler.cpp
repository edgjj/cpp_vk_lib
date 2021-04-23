#include "events/handlers/attachment_handler.hpp"

#include "simdjson.h"

static std::shared_ptr<vk::attachment::photo> get_photo(const simdjson::dom::element& attachment)
{
    return std::make_shared<vk::attachment::photo>(attachment["photo"]["owner_id"].get_int64(), attachment["photo"]["id"].get_int64());
}
static std::shared_ptr<vk::attachment::video> get_video(const simdjson::dom::element& attachment)
{
    return std::make_shared<vk::attachment::video>(attachment["video"]["owner_id"].get_int64(), attachment["video"]["id"].get_int64());
}
static std::shared_ptr<vk::attachment::document> get_doc(const simdjson::dom::element& attachment)
{
    return std::make_shared<vk::attachment::document>(
        attachment["doc"]["owner_id"].get_int64(),
        attachment["doc"]["id"].get_int64(),
        attachment["doc"]["url"].get_string());
}
static std::shared_ptr<vk::attachment::audio> get_audio(const simdjson::dom::element& attachment)
{
    return std::make_shared<vk::attachment::audio>(attachment["audio"]["owner_id"].get_int64(), attachment["audio"]["id"].get_int64());
}
static std::shared_ptr<vk::attachment::audio_message> get_audio_message(const simdjson::dom::element& attachment)
{
    return std::make_shared<vk::attachment::audio_message>(
        attachment["audio_message"]["owner_id"].get_int64(),
        attachment["audio_message"]["id"].get_int64(),
        attachment["audio_message"]["link_ogg"].get_string(),
        attachment["audio_message"]["link_mp3"].get_string());
}
static std::shared_ptr<vk::attachment::wall> get_wall(const simdjson::dom::element& attachment)
{
    return std::make_shared<vk::attachment::wall>(attachment["wall"]["from_id"].get_int64(), attachment["wall"]["id"].get_int64());
}

vk::attachment::attachments_t vk::event::attachment_handler::try_get(const simdjson::dom::array& attachments) const
{
    attachment::attachments_t attachment_list;
    for (const simdjson::dom::element& attachment : attachments)
    {
        std::string type = attachment["type"].get_string().take_value().data();
        if (type == "photo")
        {
            attachment_list.emplace_back(get_photo(attachment));
        }
        if (type == "video")
        {
            attachment_list.emplace_back(get_video(attachment));
        }
        if (type == "doc")
        {
            attachment_list.emplace_back(get_doc(attachment));
        }
        if (type == "audio")
        {
            attachment_list.emplace_back(get_audio(attachment));
        }
        if (type == "wall")
        {
            attachment_list.emplace_back(get_wall(attachment));
        }
        if (type == "audio_message")
        {
            attachment_list.emplace_back(get_audio_message(attachment));
        }
    }
    return attachment_list;
}
