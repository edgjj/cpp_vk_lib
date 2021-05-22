#include "../../lib/include/cpp_vk_lib/methods/messages.hpp"
#include "../../lib/include/cpp_vk_lib/methods/utility/message_constructor.hpp"

#include <gtest/gtest.h>

TEST(config, basic_field_access)
{
//    vk::method::message_constructor constructor(vk::method::messages::disable_mentions);

//    for (auto&& element : std::map<std::string, std::string>{{"random_id", "0"}, {"disable_mentions", "1"}})
//    {
//        ASSERT_EQ(constructor.map()[element.first], element.second);
//    }
}

TEST(config, custom_field_access)
{
//    vk::method::message_constructor constructor(vk::method::messages::disable_mentions);

//    constructor
//        .param("param1", "value1")
//        .param("param2", "value2");

//    for (auto&& element :
//         std::map<std::string, std::string>{{"random_id", "0"}, {"disable_mentions", "1"}, {"param1", "value1"}, {"param2", "value2"}})
//    {
//        ASSERT_EQ(constructor.map()[element.first], element.second);
//    }
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
