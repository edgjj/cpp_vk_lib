#ifndef VK_WALL_REPLY_NEW_TESTS_H
#define VK_WALL_REPLY_NEW_TESTS_H

#include <gtest/gtest.h>

#include "simdjson.h"

#include "events/wall_reply_new.hpp"


TEST(wall_reply_new, default_event) {
  simdjson::dom::parser parser;
  simdjson::dom::element event_object = parser.load("json_schema/wall_reply_new.json");
  vk::event::wall_reply_new event(std::move(event_object));
  ASSERT_EQ(312, event.id());
  ASSERT_EQ(499047616, event.from_id());
  ASSERT_EQ(310, event.post_id());
  ASSERT_EQ(-192764727, event.owner_id());
  ASSERT_EQ("123", event.text());
}

#endif // VK_WALL_REPLY_NEW_TESTS_H
