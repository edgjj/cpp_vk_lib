#include "cpp_vk_lib/vk/methods/message_constructor.hpp"
#include "cpp_vk_lib/vk/api_constants.hpp"

#include "cpp_vk_lib/vk/config/config.hpp"
#include "cpp_vk_lib/vk/setup_logger.hpp"

#include <gtest/gtest.h>

TEST(methods, method_construct)
{
    constexpr size_t test_chat_id = vk::api_constants::chat_id_constant + 1;

    vk::method::group_constructor constructor;
    constructor
        .method("messages.send")
        .param("peer_id", std::to_string(test_chat_id))
        .param("text", "methods::method_construct")
        .perform_request();
}
