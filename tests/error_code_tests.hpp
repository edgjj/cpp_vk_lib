#include "vk/include/exception/error_code.hpp"
#include "vk/include/setup_logger.hpp"

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
