#ifndef VK_ATTACHMENT_HPP
#define VK_ATTACHMENT_HPP

#include "cpp_vk_lib/vk/error/exception.hpp"

#include <memory>
#include <string>

namespace vk::attachment {

class base
{
public:
    explicit base(std::string_view type, int32_t owner_id, int32_t id);
    virtual ~base() = default;

    std::string value() const;
    const std::string& type() const noexcept;

private:
    std::string attachment_type_;
    int32_t owner_id_;
    int32_t id_;
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
    std::string raw_url_;
};

class wall : public base
{
public:
    explicit wall(int32_t id, int32_t from_id);
};

class audio_message : public base
{
public:
    explicit audio_message(
        int32_t owner_id,
        int32_t id,
        std::string_view raw_ogg,
        std::string_view raw_mp3);

    const std::string& raw_ogg() const noexcept;
    const std::string& raw_mp3() const noexcept;

private:
    std::string raw_ogg_;
    std::string raw_mp3_;
};

/*!
 * \brief Try to cast base attachment to derived
 *
 * \throws exception::bad_cast_error
 */
template <typename Attachment>
std::shared_ptr<Attachment> cast(const std::shared_ptr<base>& pointer)
{
    if (auto* casted = static_cast<Attachment*>(pointer.get())) {
        return std::shared_ptr<Attachment>(pointer, casted);
    }

    throw exception::bad_cast_error<base, Attachment>();
}

using attachment_ptr_t = std::shared_ptr<base>;

}// namespace vk::attachment

#endif// VK_ATTACHMENT_HPP
