#ifndef VK_SPLIT_TEST_H
#define VK_SPLIT_TEST_H

#include <gtest/gtest.h>
#include "cpp_vk_lib/string_utils/string_utils.hpp"


namespace util = vk::string_utils;

TEST(split, split) {
  std::vector<std::string_view> v1{"1", "2", "3"};
  std::vector<std::string_view> v2{"!", "?", ":"};
  std::vector<std::string_view> v3{"1"};
  std::vector<std::string_view> v4{"1","1","1","1"};
  std::vector<std::string_view> v5{"text1","text2","text3"};

  ASSERT_EQ(util::split("1 2 3", ' '), v1);
  ASSERT_EQ(util::split("! ? :", ' '), v2);
  ASSERT_EQ(util::split("1", ' '), v3);
  ASSERT_EQ(util::split("1?1?1?1", '?'), v4);
  ASSERT_EQ(util::split("text1,text2,text3", ','), v5);
}
#endif // VK_SPLIT_TEST_H
