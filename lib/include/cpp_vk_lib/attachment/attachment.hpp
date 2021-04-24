#ifndef VK_ATTACHMENT_H
#define VK_ATTACHMENT_H

#include <memory>
#include <string>
#include <vector>

namespace vk {
/*!
 * @namespace Different attachment types and cast functions to it.
 */
namespace attachment {

class base
{
public:
    explicit base(std::string_view type_, std::int32_t owner_id_, std::int32_t id_)
      : m_attachment_type(type_)
      , m_owner_id(owner_id_)
      , m_id(id_)
    {}
    virtual ~base() = default;
    std::string value() const noexcept
    {
        return m_attachment_type + std::to_string(m_owner_id) + '_' + std::to_string(m_id);
    }
    std::string_view type() const noexcept
    {
        return m_attachment_type;
    }

protected:
    std::string m_attachment_type;
    std::int32_t m_owner_id;
    std::int32_t m_id;
};

class photo : public base
{
public:
    explicit photo(std::int32_t owner_id_, std::int32_t id_)
      : base("photo", owner_id_, id_)
    {}
};

class video : public base
{
public:
    explicit video(std::int32_t owner_id_, std::int32_t id_)
      : base("video", owner_id_, id_)
    {}
};

class audio : public base
{
public:
    explicit audio(std::int32_t owner_id_, std::int32_t id_)
      : base("audio", owner_id_, id_)
    {}
};

class document : public base
{
public:
    explicit document(std::int32_t owner_id_, std::int32_t id_, std::string_view url)
      : base("doc", owner_id_, id_)
      , _raw_url(url)
    {}
    std::string_view raw_url() const noexcept
    {
        return _raw_url;
    }

private:
    std::string _raw_url;
};

class wall : public base
{
public:
    explicit wall(std::int32_t id_, std::int32_t from_id_)
      : base("wall", from_id_, id_)
    {}
};

class audio_message : public base
{
public:
    explicit audio_message(std::int32_t owner_id_, std::int32_t id_, std::string_view raw_ogg, std::string_view raw_mp3)
      : base("audio_message", owner_id_, id_)
      , _raw_ogg(raw_ogg)
      , _raw_mp3(raw_mp3)
    {}
    std::string_view raw_ogg() const noexcept
    {
        return _raw_ogg;
    }
    std::string_view raw_mp3() const noexcept
    {
        return _raw_mp3;
    }

private:
    std::string _raw_ogg;
    std::string _raw_mp3;
};

template <typename _Attachment>
std::shared_ptr<_Attachment> cast(const std::shared_ptr<base>& pointer) noexcept
{
    return std::static_pointer_cast<_Attachment>(pointer);
}

using attachments_t = std::vector<std::shared_ptr<attachment::base>>;
}// namespace attachment
}// namespace vk
#endif// VK_ATTACHMENT_H
