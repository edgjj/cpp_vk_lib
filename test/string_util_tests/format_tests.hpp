#ifndef VK_FORMAT_TEST_H
#define VK_FORMAT_TEST_H

#include <gtest/gtest.h>
#include "string_utils/string_utils.hpp"


namespace util = vk::string_utils;

TEST(format, format) {
  ASSERT_EQ(util::format("text"), "text");
  ASSERT_EQ(util::format("text: {}", 1), "text: 1");
  ASSERT_EQ(util::format("text: {}", 1ULL), "text: 1");
  ASSERT_EQ(util::format("text: {}", "1"), "text: 1");

  ASSERT_EQ(util::format("arg1: {}, arg2: {}, arg3: {}", "1", "2", "3"), "arg1: 1, arg2: 2, arg3: 3");
  ASSERT_EQ(util::format("arg1: {}, arg2: {}, arg3: {}", 1, 2, 3), "arg1: 1, arg2: 2, arg3: 3");
  ASSERT_EQ(util::format("arg1: {}, arg2: {}, arg3: {}", 1ULL, 2ULL, 3ULL), "arg1: 1, arg2: 2, arg3: 3");

  std::string_view text = "1";

  ASSERT_EQ(util::format("text: {}", text), "text: 1");
  ASSERT_EQ(util::format("arg1: {}, arg2: {}, arg3: {}", text, text, text), "arg1: 1, arg2: 1, arg3: 1");
}

#endif // VK_FORMAT_TEST_H
