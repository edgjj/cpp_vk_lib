#ifndef VK_ATTACHMENT_TESTS_H
#define VK_ATTACHMENT_TESTS_H

#include <gtest/gtest.h>
#include "attachment/attachment.hpp"


namespace att = vk::attachment;

TEST(attachment, photo) {
  att::photo_attachment photo(100, 200);

  ASSERT_EQ(photo.value(), "photo100_200");
  ASSERT_EQ(photo.type(), "photo");
}

TEST(attachment, video) {
  att::video_attachment video(100, 200);

  ASSERT_EQ(video.value(), "video100_200");
  ASSERT_EQ(video.type(), "video");
}

TEST(attachment, audio) {
  att::audio_attachment audio(100, 200);

  ASSERT_EQ(audio.value(), "audio100_200");
  ASSERT_EQ(audio.type(), "audio");
}

TEST(attachment, document) {
  att::document_attachment doc(100, 200, "https://www.something");

  ASSERT_EQ(doc.value(), "doc100_200");
  ASSERT_EQ(doc.type(), "doc");
  ASSERT_EQ(doc.raw_url(), "https://www.something");
}

TEST(attachment, audio_message) {
  att::audio_message_attachment audio_message(100, 200, "https://raw.ogg.link", "https://raw.mp3.link");

  ASSERT_EQ(audio_message.value(), "audio_message100_200");
  ASSERT_EQ(audio_message.type(), "audio_message");
  ASSERT_EQ(audio_message.raw_ogg(), "https://raw.ogg.link");
  ASSERT_EQ(audio_message.raw_mp3(), "https://raw.mp3.link");
}

TEST(attachment, wall) {
  att::wall_attachment wall(100, 200);

  ASSERT_EQ(wall.value(), "wall200_100");
  ASSERT_EQ(wall.type(), "wall");
}

#endif // VK_ATTACHMENT_TESTS_H
