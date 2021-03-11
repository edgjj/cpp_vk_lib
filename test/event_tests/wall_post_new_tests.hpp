#ifndef VK_WALL_POST_NEW_TESTS_H
#define VK_WALL_POST_NEW_TESTS_H

#include <gtest/gtest.h>

#include "simdjson.h"

#include "cpp_vk_lib/events/wall_post_new.hpp"


TEST(wall_post_new, default_event) {
  simdjson::dom::parser parser;
  simdjson::dom::element event_object = parser.load("json_schema/wall_post_new.json");
  vk::event::wall_post_new event(std::move(event_object));
  ASSERT_EQ(309, event.id());
  ASSERT_EQ(-192764727, event.from_id());
  ASSERT_EQ(-192764727, event.owner_id());
  ASSERT_FALSE(event.marked_as_ads());
  ASSERT_EQ("123", event.text());
  ASSERT_TRUE(event.can_edit());
  ASSERT_TRUE(event.can_delete());
  ASSERT_EQ(1, event.attachments().size());
  ASSERT_EQ("photo-192764727_457350091", event.attachments()[0]->value());
}

#endif // VK_WALL_POST_NEW_TESTS_H
