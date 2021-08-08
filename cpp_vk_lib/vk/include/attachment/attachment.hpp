#ifndef VK_ATTACHMENT_HPP
#define VK_ATTACHMENT_HPP

#include "vk/include/exception/exception.hpp"

#include <memory>
#include <string>

namespace vk {
/*!
 * @namespace Different attachment types and cast function to it.
 */
namespace attachment {

class base
{
public:
    explicit base(std::string_view type, int32_t owner_id, int32_t id);
    virtual ~base() = default;

    std::string value() const;
    const std::string& type() const noexcept;

private:
    std::string m_attachment_type;
    int32_t m_owner_id;
    int32_t m_id;
};

class photo : public base
{
public:
    explicit photo(int32_t owner_id, int32_t id);
};

class video : public base
{
public:
    explicit video(int32_t owner_id, int32_t id);
};

class audio : public base
{
public:
    explicit audio(int32_t owner_id, int32_t id);
};

class document : public base
{
public:
    explicit document(int32_t owner_id, int32_t id, std::string_view url);

    const std::string& raw_url() const noexcept;

private:
    std::string m_raw_url;
};

class wall : public base
{
public:
    explicit wall(int32_t id, int32_t from_id);
};

class audio_message : public base
{
public:
    explicit audio_message(int32_t owner_id, int32_t id, std::string_view raw_ogg, std::string_view raw_mp3);

    const std::string& raw_ogg() const noexcept;
    const std::string& raw_mp3() const noexcept;

private:
    std::string m_raw_ogg;
    std::string m_raw_mp3;
};

template <typename Attachment>
std::shared_ptr<Attachment> cast(const std::shared_ptr<base>& pointer)
{
    if (auto* casted = static_cast<Attachment*>(pointer.get())) {
        return std::shared_ptr<Attachment>(pointer, casted);
    }

    throw exception::bad_cast_error<base, Attachment>();
}

using attachment_ptr_t = std::shared_ptr<attachment::base>;

}// namespace attachment
}// namespace vk

#endif// VK_ATTACHMENT_HPP