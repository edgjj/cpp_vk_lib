#include "cpp_vk_lib/vk/error/error_code.hpp"
#include "cpp_vk_lib/vk/setup_logger.hpp"

#include <gtest/gtest.h>

TEST(error_code, error_code)
{
    vk::error_code errc;
    ASSERT_FALSE(errc);
    errc.assign("Some error");
    ASSERT_TRUE(errc);
    errc.clear();
    ASSERT_FALSE(errc);
}
