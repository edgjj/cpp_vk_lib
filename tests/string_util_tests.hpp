#include "runtime/include/string_utils/string_utils.hpp"
#include "vk/include/setup_logger.hpp"

#include <gtest/gtest.h>

#include <list>
#include <deque>
#include <forward_list>

namespace util = runtime::string_utils;

TEST(string_utils, utf_to_lower)
{
    ASSERT_EQ(util::utf8_to_lower("ААА"), "ааа");
    ASSERT_EQ(util::utf8_to_lower("ЯЯЯ"), "яяя");
    ASSERT_EQ(util::utf8_to_lower("ЭЭЭ"), "эээ");
    ASSERT_EQ(util::utf8_to_lower("111"), "111");
    ASSERT_EQ(util::utf8_to_lower("{!}"), "{!}");
}

TEST(string_utils, utf_to_upper)
{
    ASSERT_EQ(util::utf8_to_upper("ааа"), "ААА");
    ASSERT_EQ(util::utf8_to_upper("яяя"), "ЯЯЯ");
    ASSERT_EQ(util::utf8_to_upper("ффф"), "ФФФ");
    ASSERT_EQ(util::utf8_to_upper("ыыы"), "ЫЫЫ");
    ASSERT_EQ(util::utf8_to_upper("111"), "111");
    ASSERT_EQ(util::utf8_to_upper("{!}"), "{!}");
}

TEST(string_utils, ascii_to_lower)
{
    ASSERT_EQ(util::ascii_to_lower("AAA"), "aaa");
    ASSERT_EQ(util::ascii_to_lower("ZZZ"), "zzz");
    ASSERT_EQ(util::ascii_to_lower("FFF"), "fff");
    ASSERT_EQ(util::ascii_to_lower("111"), "111");
    ASSERT_EQ(util::ascii_to_lower("{!}"), "{!}");
}

TEST(string_utils, ascii_to_upper)
{
    ASSERT_EQ(util::ascii_to_upper("aaa"), "AAA");
    ASSERT_EQ(util::ascii_to_upper("zzz"), "ZZZ");
    ASSERT_EQ(util::ascii_to_upper("fff"), "FFF");
    ASSERT_EQ(util::ascii_to_upper("sss"), "SSS");
    ASSERT_EQ(util::ascii_to_upper("111"), "111");
    ASSERT_EQ(util::ascii_to_upper("{!}"), "{!}");
}

TEST(string_utils, format)
{
    ASSERT_EQ(util::format("text"), "text");
    ASSERT_EQ(util::format("text: {}", 1), "text: 1");
    ASSERT_EQ(util::format("text: {}", 1ULL), "text: 1");
    ASSERT_EQ(util::format("text: {}", "1"), "text: 1");

    ASSERT_EQ(util::format("arg1: {}, arg2: {}, arg3: {}", "1", "2", "3"), "arg1: 1, arg2: 2, arg3: 3");
    ASSERT_EQ(util::format("arg1: {}, arg2: {}, arg3: {}", 1, 2, 3), "arg1: 1, arg2: 2, arg3: 3");
    ASSERT_EQ(util::format("arg1: {}, arg2: {}, arg3: {}", 1ULL, 2ULL, 3ULL), "arg1: 1, arg2: 2, arg3: 3");

    const std::string_view text = "1";

    ASSERT_EQ(util::format("text: {}", text), "text: 1");
    ASSERT_EQ(util::format("arg1: {}, arg2: {}, arg3: {}", text, text, text), "arg1: 1, arg2: 1, arg3: 1");
}

TEST(string_utils, initializer_list_join)
{
    ASSERT_EQ(util::join({1, 2, 3}, ','), "1,2,3");
    ASSERT_EQ(util::join({1ULL, 2ULL, 3ULL}, ','), "1,2,3");
    ASSERT_EQ(util::join({1, 2, 3}, ','), "1,2,3");
    ASSERT_EQ(util::join({"1", "2", "3"}, ','), "1,2,3");
}

TEST(string_utils, vector_join)
{
    const std::vector<std::string> string_container{"1", "2", "3"};
    const std::vector<int> int_container{1, 2, 3};
    ASSERT_EQ(util::join<std::string>(string_container, ','), "1,2,3");
    ASSERT_EQ(util::join<int>(int_container, ','), "1,2,3");
}

TEST(string_utils, deque_join)
{
    const std::deque<std::string> string_container{"1", "2", "3"};
    const std::deque<int> int_container{1, 2, 3};
    ASSERT_EQ(util::join<std::string>(string_container, ','), "1,2,3");
    ASSERT_EQ(util::join<int>(int_container, ','), "1,2,3");
}

TEST(string_utils, list_join)
{
    const std::list<std::string> string_container{"1", "2", "3"};
    const std::list<int> int_container{1, 2, 3};
    ASSERT_EQ(util::join<std::string>(string_container, ','), "1,2,3");
    ASSERT_EQ(util::join<int>(int_container, ','), "1,2,3");
}

TEST(string_utils, forward_list_join)
{
    const std::forward_list<std::string> string_container{"1", "2", "3"};
    const std::forward_list<int> int_container{1, 2, 3};
    ASSERT_EQ(util::join<std::string>(string_container, ','), "1,2,3");
    ASSERT_EQ(util::join<int>(int_container, ','), "1,2,3");
}

TEST(string_utils, array_join)
{
    const std::array<std::string, 3> string_container{"1", "2", "3"};
    const std::array<int, 3> int_container{1, 2, 3};
    ASSERT_EQ(util::join<std::string>(string_container, ','), "1,2,3");
    ASSERT_EQ(util::join<int>(int_container, ','), "1,2,3");
}

TEST(string_utils, split_by_symbol)
{
    const std::vector<std::string_view> v1{"1", "2", "3"};
    const std::vector<std::string_view> v2{"!", "?", ":"};
    const std::vector<std::string_view> v3{"1"};
    const std::vector<std::string_view> v4{"1", "1", "1", "1"};
    const std::vector<std::string_view> v5{"text1", "text2", "text3"};

    ASSERT_EQ(util::split("1 2 3", ' '), v1);
    ASSERT_EQ(util::split("! ? :", ' '), v2);
    ASSERT_EQ(util::split("1", ' '), v3);
    ASSERT_EQ(util::split("1?1?1?1", '?'), v4);
    ASSERT_EQ(util::split("text1,text2,text3", ','), v5);
}

TEST(string_utils, split_by_string)
{
    const std::vector<std::string_view> v1{"1", "2", "3"};
    const std::vector<std::string_view> v2{"!", "?", ":"};
    const std::vector<std::string_view> v3{"1"};
    const std::vector<std::string_view> v4{"1", "1", "1", "1"};
    const std::vector<std::string_view> v5{"text1", "text2", "text3"};

    ASSERT_EQ(util::split("1!?2!?3", "!?"), v1);
    ASSERT_EQ(util::split("!\\\\?\\\\:", "\\\\"), v2);
    ASSERT_EQ(util::split("1", " "), v3);
    ASSERT_EQ(util::split("1??1??1??1", "??"), v4);
    ASSERT_EQ(util::split("text1,,,text2,,,text3", ",,,"), v5);
}

TEST(string_utils, whitespace_split)
{
    const std::vector<std::string_view> v1{"1", "2", "3"};
    const std::vector<std::string_view> v2{"!", "?", ":"};
    const std::vector<std::string_view> v3{"1"};

    ASSERT_EQ(util::whitespace_split("1\n\n\n\t\r\v\f2   3"), v1);
    ASSERT_EQ(util::whitespace_split("!\n\n\n\t\r\v\f?\n\n\n\t\r\v\f:"), v2);
    ASSERT_EQ(util::whitespace_split("\n\n\n\t\r\v\f1\n\n\n\t\r\v\f"), v3);
}

TEST(string_utils, lazy_split)
{
    const std::array<const char*, 3> assertion_data_1 = {
        "1", "2", "3"
    };
    const std::array<const char*, 3> assertion_data_2 = {
        "\x60", "\x60", "\x60"
    };
    size_t offset_1 = 0;
    size_t offset_2 = 0;
    for (auto word : util::lazy_split("1___2___3", "___")) {
        ASSERT_EQ(word, assertion_data_1[offset_1++]);
    }
    for (auto word : util::lazy_split("\x60\x32\x60\x32\x60", "\x32")) {
        ASSERT_EQ(word, assertion_data_2[offset_2++]);
    }
}