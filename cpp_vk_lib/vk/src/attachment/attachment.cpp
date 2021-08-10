#include "vk/include/attachment/attachment.hpp"

#include "runtime/include/string_utils/string_utils.hpp"

namespace vk::attachment {

base::base(std::string_view type, int32_t owner_id, int32_t id) : attachment_type_(type), owner_id_(owner_id), id_(id) {}

std::string base::value() const { return runtime::string_utils::format("{}{}_{}", attachment_type_, owner_id_, id_); }

const std::string& base::type() const noexcept { return attachment_type_; }

photo::photo(int32_t owner_id, int32_t id) : base("photo", owner_id, id) {}
video::video(int32_t owner_id, int32_t id) : base("video", owner_id, id) {}
audio::audio(int32_t owner_id, int32_t id) : base("audio", owner_id, id) {}

document::document(int32_t owner_id, int32_t id, std::string_view url) : base("doc", owner_id, id), raw_url_(url) {}

const std::string& document::raw_url() const noexcept { return raw_url_; }

wall::wall(int32_t id, int32_t from_id) : base("wall", from_id, id) {}

audio_message::audio_message(int32_t owner_id, int32_t id, std::string_view raw_ogg, std::string_view raw_mp3)
  : base("audio_message", owner_id, id)
  , raw_ogg_(raw_ogg)
  , raw_mp3_(raw_mp3) {}

const std::string& audio_message::raw_ogg() const noexcept { return raw_ogg_; }
const std::string& audio_message::raw_mp3() const noexcept { return raw_mp3_; }

}// namespace vk::attachment