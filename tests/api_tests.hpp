#include "vk/include/methods/utility/message_constructor.hpp"
#include "vk/include/api_constants.hpp"

#include "vk/include/config/loader.hpp"
#include "vk/include/setup_logger.hpp"

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
