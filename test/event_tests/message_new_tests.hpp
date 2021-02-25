#ifndef VK_MESSAGE_NEW_EVENT_TESTS_H
#define VK_MESSAGE_NEW_EVENT_TESTS_H

#include <gtest/gtest.h>

#include "simdjson.h"

#include "events/common_event.hpp"


TEST(message_new, default_event) {
  simdjson::dom::parser parser;
  simdjson::dom::element event_object = parser.load("json_schema/message_new.json");
  vk::event::message_new event(std::move(event_object));
  ASSERT_EQ("123", event.text());
  ASSERT_EQ(499047616, event.from_id());
  ASSERT_EQ(2000000008, event.peer_id());
  ASSERT_EQ(120470, event.conversation_message_id());
  ASSERT_EQ(false, event.has_action());
  ASSERT_EQ(false, event.has_fwd_messages());
  ASSERT_EQ(false, event.has_reply());
}

TEST(message_new, event_attachments) {
  simdjson::dom::parser parser;
  simdjson::dom::element event_object = parser.load("json_schema/message_new.json");
  vk::event::message_new event(std::move(event_object));
  auto photo_attachment = event.attachments()[0];
  ASSERT_EQ(1, event.attachments().size());
  ASSERT_EQ("photo", photo_attachment->type());
  ASSERT_EQ("photo499047616_457273210", photo_attachment->value());
}

#endif // VK_MESSAGE_NEW_EVENT_TESTS_H
