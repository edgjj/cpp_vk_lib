#include "../../lib/include/cpp_vk_lib/exception/exception.hpp"

#include <gtest/gtest.h>

TEST(exception, access_error)
{
    const size_t id = 224;
    try
    {
        throw vk::exception::access_error(id, "text");
    } catch (std::exception& error)
    {
        ASSERT_EQ(std::string(error.what()), "[vk.exception.access_error.224]: text");
    }
}

TEST(exception, upload_error)
{
    const size_t id = 224;
    try
    {
        throw vk::exception::upload_error(id, "text");
    } catch (std::exception& error)
    {
        ASSERT_EQ(std::string(error.what()), "[vk.exception.upload_error.224]: text");
    }
}

TEST(exception, invalid_parameter_error)
{
    const size_t id = 224;
    try
    {
        throw vk::exception::invalid_parameter_error(id, "text");
    } catch (std::exception& error)
    {
        ASSERT_EQ(std::string(error.what()), "[vk.exception.invalid_parameter_error.224]: text");
    }
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
