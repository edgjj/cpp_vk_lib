#include "vk/include/attachment/attachment.hpp"
#include "vk/include/setup_logger.hpp"
#include <gtest/gtest.h>

namespace att = vk::attachment;

TEST(attachment, photo)
{
    att::photo photo(100, 200);

    ASSERT_EQ(photo.value(), "photo100_200");
    ASSERT_EQ(photo.type(), "photo");
}

TEST(attachment, video)
{
    att::video video(100, 200);

    ASSERT_EQ(video.value(), "video100_200");
    ASSERT_EQ(video.type(), "video");
}

TEST(attachment, audio)
{
    att::audio audio(100, 200);

    ASSERT_EQ(audio.value(), "audio100_200");
    ASSERT_EQ(audio.type(), "audio");
}

TEST(attachment, document)
{
    att::document doc(100, 200, "https://www.something");

    ASSERT_EQ(doc.value(), "doc100_200");
    ASSERT_EQ(doc.type(), "doc");
    ASSERT_EQ(doc.raw_url(), "https://www.something");
}

TEST(attachment, audio_message)
{
    att::audio_message audio_message(100, 200, "https://raw.ogg.link", "https://raw.mp3.link");

    ASSERT_EQ(audio_message.value(), "audio_message100_200");
    ASSERT_EQ(audio_message.type(), "audio_message");
    ASSERT_EQ(audio_message.raw_ogg(), "https://raw.ogg.link");
    ASSERT_EQ(audio_message.raw_mp3(), "https://raw.mp3.link");
}

TEST(attachment, wall)
{
    att::wall wall(100, 200);

    ASSERT_EQ(wall.value(), "wall200_100");
    ASSERT_EQ(wall.type(), "wall");
}

TEST(attachment, photo_cast)
{
    auto photo_attachment = vk::attachment::cast<att::photo>(std::make_shared<att::base>("photo", 100, 200));
    ASSERT_TRUE(photo_attachment);
    ASSERT_EQ(photo_attachment->value(), "photo100_200");
}

TEST(attachment, video_cast)
{
    auto audio_attachment = vk::attachment::cast<att::video>(std::make_shared<att::base>("video", 100, 200));
    ASSERT_TRUE(audio_attachment);
    ASSERT_EQ(audio_attachment->value(), "video100_200");
}

TEST(attachment, audio_cast)
{
    auto audio_attachment = vk::attachment::cast<att::document>(std::make_shared<att::base>("doc", 100, 200));
    ASSERT_TRUE(audio_attachment);
    ASSERT_EQ(audio_attachment->value(), "doc100_200");
}

TEST(attachment, wall_cast)
{
    auto audio_attachment = vk::attachment::cast<att::wall>(std::make_shared<att::base>("wall", 100, 200));
    ASSERT_TRUE(audio_attachment);
    ASSERT_EQ(audio_attachment->value(), "wall100_200");
}

TEST(attachment, audio_message_cast)
{
    auto audio_attachment = vk::attachment::cast<att::audio_message>(std::make_shared<att::base>("audio_message", 100, 200));
    ASSERT_TRUE(audio_attachment);
    ASSERT_EQ(audio_attachment->value(), "audio_message100_200");
}

TEST(attachment, raw_class_cast)
{
    auto audio = std::make_shared<att::audio>(100, 200);

    class empty_attachment : public vk::attachment::base {};

    ASSERT_TRUE(vk::attachment::cast<empty_attachment>(audio));
}

int main(int argc, char* argv[])
{
    vk::setup_logger("trace");

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
