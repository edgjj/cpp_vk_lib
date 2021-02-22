#ifndef VK_JOIN_TEST_H
#define VK_JOIN_TEST_H

#include <list>
#include <forward_list>
#include <array>
#include <deque>

#include <gtest/gtest.h>
#include "string_utils/string_utils.hpp"


namespace util = vk::string_utils;

TEST(join, initializer_list) {
  ASSERT_EQ(util::join({1,2,3}), "1,2,3");
  ASSERT_EQ(util::join({1ULL,2ULL,3ULL}), "1,2,3");
  ASSERT_EQ(util::join({1,2,3}), "1,2,3");
  ASSERT_EQ(util::join({"1","2","3"}), "1,2,3");
}

TEST(join, vector) {
  std::vector<std::string> string_container{"1","2","3"};
  std::vector<int> int_container{1,2,3};
  ASSERT_EQ(util::join<std::string>(string_container), "1,2,3");
  ASSERT_EQ(util::join<int>(int_container), "1,2,3");
}

TEST(join, deque) {
  std::deque<std::string> string_container{"1","2","3"};
  std::deque<int> int_container{1,2,3};
  ASSERT_EQ(util::join<std::string>(string_container), "1,2,3");
  ASSERT_EQ(util::join<int>(int_container), "1,2,3");
}

TEST(join, list) {
  std::list<std::string> string_container{"1","2","3"};
  std::list<int> int_container{1,2,3};
  ASSERT_EQ(util::join<std::string>(string_container), "1,2,3");
  ASSERT_EQ(util::join<int>(int_container), "1,2,3");
}

TEST(join, forward_list) {
  std::forward_list<std::string> string_container{"1","2","3"};
  std::forward_list<int> int_container{1,2,3};
  ASSERT_EQ(util::join<std::string>(string_container), "1,2,3");
  ASSERT_EQ(util::join<int>(int_container), "1,2,3");
}

TEST(join, array) {
  std::array<std::string, 3> string_container{"1","2","3"};
  std::array<int, 3> int_container{1,2,3};
  ASSERT_EQ(util::join<std::string>(string_container), "1,2,3");
  ASSERT_EQ(util::join<int>(int_container), "1,2,3");
}


#endif // VK_JOIN_TEST_H
