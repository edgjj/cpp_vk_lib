#ifndef VK_ATTACHMENT_H
#define VK_ATTACHMENT_H

#include <string>
#include <memory>
#include <vector>

#include "misc/cppdefs.hpp"


namespace vk {
/*!
 * @namespace Different attachment types and cast functions to it.
 */
namespace attachment {

class vk_export base {
public:
  explicit
  base (std::int32_t owner_id_, std::int32_t id_)
    : owner_id(owner_id_), id(id_)
  { }
  virtual ~base() = default;
  virtual std::string value() const noexcept = 0;
  virtual std::string type()  const noexcept = 0;

protected:
  std::int32_t owner_id;
  std::int32_t id;
};

class vk_export photo : public base {
public:
  explicit
  photo(std::int32_t owner_id_, std::int32_t id_)
    : base(owner_id_, id_)
  { }
  std::string value() const noexcept override { return "photo" + std::to_string(owner_id) + '_' + std::to_string(id); }
  std::string type()  const noexcept override { return "photo"; }
};

class vk_export video : public base {
public:
  explicit
  video(std::int32_t owner_id_, std::int32_t id_)
    : base(owner_id_, id_)
  { }
  std::string value() const noexcept override { return "video" + std::to_string(owner_id) + '_' + std::to_string(id); }
  std::string type()  const noexcept override { return "video"; }
};

class vk_export audio : public base {
public:
  explicit
  audio(std::int32_t owner_id_, std::int32_t id_)
    : base(owner_id_, id_)
  { }
  std::string value() const noexcept override { return "audio" + std::to_string(owner_id) + '_' + std::to_string(id); }
  std::string type()  const noexcept override { return "audio"; }
};

class vk_export document : public base {
public:
  explicit
  document(std::int32_t owner_id_, std::int32_t id_, std::string_view url)
    : base(owner_id_, id_), _raw_url(url.data())
  { }
  std::string value()   const noexcept override { return "doc" + std::to_string(owner_id) + '_' + std::to_string(id); }
  std::string type()    const noexcept override { return "doc"; }
  std::string raw_url() const noexcept { return _raw_url; }

private:
  const char* _raw_url;
};

class vk_export audio_message : public base {
public:
  explicit
  audio_message(std::int32_t owner_id_, std::int32_t id_, std::string_view raw_ogg, std::string_view raw_mp3)
    : base(owner_id_, id_), _raw_ogg(raw_ogg.data()), _raw_mp3(raw_mp3.data())
  { }
  std::string value()   const noexcept override { return "audio_message" + std::to_string(owner_id) + '_' + std::to_string(id); }
  std::string type()    const noexcept override { return "audio_message"; }
  std::string raw_ogg() const noexcept { return _raw_ogg; }
  std::string raw_mp3() const noexcept { return _raw_mp3; }

private:
  const char* _raw_ogg;
  const char* _raw_mp3;
};

class vk_export wall : public base {
public:
  explicit
  wall(std::int32_t id_, std::int32_t from_id_)
    : base(from_id_, id_)
  { }
  std::string value()   const noexcept override { return "wall" + std::to_string(owner_id) + '_' + std::to_string(id); }
  std::string type()    const noexcept override { return "wall"; }
};

inline std::shared_ptr<photo> static_photo_cast(const std::shared_ptr<base>& pointer) noexcept {
  return std::static_pointer_cast<photo>(pointer);
}
inline std::shared_ptr<audio> static_audio_cast(const std::shared_ptr<base>& pointer) noexcept {
  return std::static_pointer_cast<audio>(pointer);
}
inline std::shared_ptr<video> static_video_cast(const std::shared_ptr<base>& pointer) noexcept {
  return std::static_pointer_cast<video>(pointer);
}
inline std::shared_ptr<document> static_document_cast(const std::shared_ptr<base>& pointer) noexcept {
  return std::static_pointer_cast<document>(pointer);
}
inline std::shared_ptr<audio_message> static_audio_message_cast(const std::shared_ptr<base>& pointer) noexcept {
  return std::static_pointer_cast<audio_message>(pointer);
}
inline std::shared_ptr<wall> static_wall_cast(const std::shared_ptr<base>& pointer) noexcept {
  return std::static_pointer_cast<wall>(pointer);
}

using attachments_t = std::vector<std::shared_ptr<attachment::base>>;
} // namespace attachment
} // namespace vk
#endif // VK_ATTACHMENT_H
