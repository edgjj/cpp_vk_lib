#ifndef VK_CONVERT_TEST_H
#define VK_CONVERT_TEST_H

#include <gtest/gtest.h>
#include "cpp_vk_lib/string_utils/string_utils.hpp"


namespace util = vk::string_utils;

TEST(convert, utf_to_lower) {
  ASSERT_EQ(util::utf8_to_lower("ААА"), "ааа");
  ASSERT_EQ(util::utf8_to_lower("ЯЯЯ"), "яяя");
  ASSERT_EQ(util::utf8_to_lower("ЭЭЭ"), "эээ");
  ASSERT_EQ(util::utf8_to_lower("111"), "111");
  ASSERT_EQ(util::utf8_to_lower("{!}"), "{!}");
}

TEST(convert, utf_to_upper) {
  ASSERT_EQ(util::utf8_to_upper("ааа"), "ААА");
  ASSERT_EQ(util::utf8_to_upper("яяя"), "ЯЯЯ");
  ASSERT_EQ(util::utf8_to_upper("ффф"), "ФФФ");
  ASSERT_EQ(util::utf8_to_upper("ыыы"), "ЫЫЫ");
  ASSERT_EQ(util::utf8_to_upper("111"), "111");
  ASSERT_EQ(util::utf8_to_upper("{!}"), "{!}");
}

TEST(convert, ascii_to_lower) {
  ASSERT_EQ(util::ascii_to_lower("AAA"), "aaa");
  ASSERT_EQ(util::ascii_to_lower("ZZZ"), "zzz");
  ASSERT_EQ(util::ascii_to_lower("FFF"), "fff");
  ASSERT_EQ(util::ascii_to_lower("111"), "111");
  ASSERT_EQ(util::ascii_to_lower("{!}"), "{!}");
}

TEST(convert, ascii_to_upper) {
  ASSERT_EQ(util::utf8_to_upper("aaa"), "AAA");
  ASSERT_EQ(util::utf8_to_upper("zzz"), "ZZZ");
  ASSERT_EQ(util::utf8_to_upper("fff"), "FFF");
  ASSERT_EQ(util::utf8_to_upper("sss"), "SSS");
  ASSERT_EQ(util::utf8_to_upper("111"), "111");
  ASSERT_EQ(util::utf8_to_upper("{!}"), "{!}");
}

#endif // VK_CONVERT_TEST_H
