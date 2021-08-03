#include "vk/include/attachment/attachment.hpp"

#include "runtime/include/string_utils/string_utils.hpp"

vk::attachment::base::base(std::string_view type, int32_t owner_id, int32_t id) : m_attachment_type(type), m_owner_id(owner_id), m_id(id) {}

std::string vk::attachment::base::value() const { return runtime::string_utils::format("{}{}_{}", m_attachment_type, m_owner_id, m_id); }

const std::string& vk::attachment::base::type() const noexcept{ return m_attachment_type; }

vk::attachment::photo::photo(int32_t owner_id, int32_t id) : base("photo", owner_id, id) {}
vk::attachment::video::video(int32_t owner_id, int32_t id) : base("video", owner_id, id) {}
vk::attachment::audio::audio(int32_t owner_id, int32_t id) : base("audio", owner_id, id) {}

vk::attachment::document::document(int32_t owner_id, int32_t id, std::string_view url)
    : base("doc", owner_id, id)
    , m_raw_url(url) {}

const std::string& vk::attachment::document::raw_url() const noexcept { return m_raw_url; }

vk::attachment::wall::wall(int32_t id, int32_t from_id) : base("wall", from_id, id) {}

vk::attachment::audio_message::audio_message(int32_t owner_id, int32_t id, std::string_view raw_ogg, std::string_view raw_mp3)
  : base("audio_message", owner_id, id)
  , m_raw_ogg(raw_ogg)
  , m_raw_mp3(raw_mp3) {}

const std::string& vk::attachment::audio_message::raw_ogg() const noexcept { return m_raw_ogg; }
const std::string& vk::attachment::audio_message::raw_mp3() const noexcept { return m_raw_mp3; }
