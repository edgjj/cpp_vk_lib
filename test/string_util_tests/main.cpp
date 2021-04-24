#include "../../lib/include/cpp_vk_lib/string_utils/string_utils.hpp"

#include <deque>
#include <forward_list>
#include <gtest/gtest.h>
#include <list>

namespace util = vk::string_utils;

TEST(convert, utf_to_lower)
{
    ASSERT_EQ(util::utf8_to_lower("ААА"), "ааа");
    ASSERT_EQ(util::utf8_to_lower("ЯЯЯ"), "яяя");
    ASSERT_EQ(util::utf8_to_lower("ЭЭЭ"), "эээ");
    ASSERT_EQ(util::utf8_to_lower("111"), "111");
    ASSERT_EQ(util::utf8_to_lower("{!}"), "{!}");
}

TEST(convert, utf_to_upper)
{
    ASSERT_EQ(util::utf8_to_upper("ааа"), "ААА");
    ASSERT_EQ(util::utf8_to_upper("яяя"), "ЯЯЯ");
    ASSERT_EQ(util::utf8_to_upper("ффф"), "ФФФ");
    ASSERT_EQ(util::utf8_to_upper("ыыы"), "ЫЫЫ");
    ASSERT_EQ(util::utf8_to_upper("111"), "111");
    ASSERT_EQ(util::utf8_to_upper("{!}"), "{!}");
}

TEST(convert, ascii_to_lower)
{
    ASSERT_EQ(util::ascii_to_lower("AAA"), "aaa");
    ASSERT_EQ(util::ascii_to_lower("ZZZ"), "zzz");
    ASSERT_EQ(util::ascii_to_lower("FFF"), "fff");
    ASSERT_EQ(util::ascii_to_lower("111"), "111");
    ASSERT_EQ(util::ascii_to_lower("{!}"), "{!}");
}

TEST(convert, ascii_to_upper)
{
    ASSERT_EQ(util::utf8_to_upper("aaa"), "AAA");
    ASSERT_EQ(util::utf8_to_upper("zzz"), "ZZZ");
    ASSERT_EQ(util::utf8_to_upper("fff"), "FFF");
    ASSERT_EQ(util::utf8_to_upper("sss"), "SSS");
    ASSERT_EQ(util::utf8_to_upper("111"), "111");
    ASSERT_EQ(util::utf8_to_upper("{!}"), "{!}");
}

TEST(format, format)
{
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

TEST(join, initializer_list)
{
    ASSERT_EQ(util::join({1, 2, 3}), "1,2,3");
    ASSERT_EQ(util::join({1ULL, 2ULL, 3ULL}), "1,2,3");
    ASSERT_EQ(util::join({1, 2, 3}), "1,2,3");
    ASSERT_EQ(util::join({"1", "2", "3"}), "1,2,3");
}

TEST(join, vector)
{
    std::vector<std::string> string_container{"1", "2", "3"};
    std::vector<int> int_container{1, 2, 3};
    ASSERT_EQ(util::join<std::string>(string_container), "1,2,3");
    ASSERT_EQ(util::join<int>(int_container), "1,2,3");
}

TEST(join, deque)
{
    std::deque<std::string> string_container{"1", "2", "3"};
    std::deque<int> int_container{1, 2, 3};
    ASSERT_EQ(util::join<std::string>(string_container), "1,2,3");
    ASSERT_EQ(util::join<int>(int_container), "1,2,3");
}

TEST(join, list)
{
    std::list<std::string> string_container{"1", "2", "3"};
    std::list<int> int_container{1, 2, 3};
    ASSERT_EQ(util::join<std::string>(string_container), "1,2,3");
    ASSERT_EQ(util::join<int>(int_container), "1,2,3");
}

TEST(join, forward_list)
{
    std::forward_list<std::string> string_container{"1", "2", "3"};
    std::forward_list<int> int_container{1, 2, 3};
    ASSERT_EQ(util::join<std::string>(string_container), "1,2,3");
    ASSERT_EQ(util::join<int>(int_container), "1,2,3");
}

TEST(join, array)
{
    std::array<std::string, 3> string_container{"1", "2", "3"};
    std::array<int, 3> int_container{1, 2, 3};
    ASSERT_EQ(util::join<std::string>(string_container), "1,2,3");
    ASSERT_EQ(util::join<int>(int_container), "1,2,3");
}

TEST(split, split)
{
    std::vector<std::string_view> v1{"1", "2", "3"};
    std::vector<std::string_view> v2{"!", "?", ":"};
    std::vector<std::string_view> v3{"1"};
    std::vector<std::string_view> v4{"1", "1", "1", "1"};
    std::vector<std::string_view> v5{"text1", "text2", "text3"};

    ASSERT_EQ(util::split("1 2 3", ' '), v1);
    ASSERT_EQ(util::split("! ? :", ' '), v2);
    ASSERT_EQ(util::split("1", ' '), v3);
    ASSERT_EQ(util::split("1?1?1?1", '?'), v4);
    ASSERT_EQ(util::split("text1,text2,text3", ','), v5);
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
