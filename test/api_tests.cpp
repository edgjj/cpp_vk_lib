#include "vk/include/methods/audio.hpp"
#include "vk/include/methods/docs.hpp"
#include "vk/include/methods/groups.hpp"
#include "vk/include/methods/messages.hpp"
#include "vk/include/methods/photos.hpp"
#include "vk/include/methods/utils.hpp"
#include "vk/include/methods/video.hpp"

#include "vk/include/config/loader.hpp"

#include <gtest/gtest.h>

#include <fstream>

constexpr char sample_config[] = R"__(
{
  "api": {
    "access_token": "7483c78eba756697ae4727e5d255d7782226d8bf4dc1a87924897e23278fddd46512c759c960a6468e4cf",
    "user_token": "not used"
  },
  "oauth": {
    "login": "not used",
    "password": "not used"
  },
  "environment": {
    "num_workers": 8,
    "log_path": "logs.txt"
  }
}
)__";

constexpr size_t test_chat_id = vk::method::utility::chat_id_constant + 1;
constexpr size_t test_group_id = 206219694;

TEST(docs, get_upload_server)
{
    vk::error_code errc;

    vk::method::docs docs(errc);
    vk::method::groups groups(errc);
    vk::method::messages messages(errc, vk::method::messages::disable_mentions);

    int64_t group_id = groups.get_by_id();
    if (errc) { ASSERT_FALSE(true && "Failed to get group id"); }

    std::string upload_server = docs.get_upload_server(group_id);
    ASSERT_FALSE(upload_server.empty());
    messages.send(test_chat_id, "docs::get_upload_server tests passed");

    std::string messages_upload_server = docs.get_messages_upload_server("doc", group_id);
    ASSERT_FALSE(messages_upload_server.empty());
    messages.send(test_chat_id, "docs::get_messages_upload_server tests passed");

    std::string wall_upload_server = docs.get_wall_upload_server(group_id);
    ASSERT_FALSE(wall_upload_server.empty());
    messages.send(test_chat_id, "docs::get_wall_upload_server tests passed");
}

TEST(groups, get_by_id)
{
    vk::error_code errc;

    vk::method::groups groups(errc);
    vk::method::messages messages(errc, vk::method::messages::disable_mentions);

    [[maybe_unused]] int64_t group_id = groups.get_by_id();
    if (errc) { ASSERT_FALSE(true && "Failed to get group id"); }

    ASSERT_EQ(group_id, test_group_id);

    messages.send(test_chat_id, "docs::get_by_id tests passed");
}

TEST(messages, send)
{
    vk::error_code errc;
    vk::method::messages messages(errc, vk::method::messages::disable_mentions);

    messages.send(test_chat_id, "messages::send test passed");
}

TEST(messages, send_with_attachments)
{
    vk::error_code errc;
    vk::method::messages messages(errc, vk::method::messages::disable_mentions);

    messages.send(test_chat_id, "messages::send_with_attachments test passed", {
        std::make_shared<vk::attachment::photo>(499047616, 457274482) });
}

TEST(messages, send_with_raw_parameters)
{
    vk::error_code errc;
    vk::method::messages messages(errc, vk::method::messages::disable_mentions);

    messages.send(test_chat_id, "messages::send_with_raw_parameters", {{"attachment", "photo499047616_457274482"}});
}

TEST(messages, edit_chat)
{
    vk::error_code errc;
    vk::method::messages messages(errc, vk::method::messages::disable_mentions);

    messages.edit_chat(test_chat_id, "Hello from Github Actions");
    messages.send(test_chat_id, "messages::edit_chat tests passed");
}

TEST(messages, get_conversation_members)
{
    vk::error_code errc;
    vk::method::messages messages(errc, vk::method::messages::disable_mentions);

    messages.send(test_chat_id, runtime::string_utils::format(
        "messages::get_conversation_members: {} members", messages.get_conversation_members(test_chat_id).size()));
}

TEST(photos, get_messages_upload_server)
{
    vk::error_code errc;
    vk::method::photos photos(errc);
    vk::method::messages messages(errc, vk::method::messages::disable_mentions);

    std::string server = photos.get_messages_upload_server(test_chat_id);

    ASSERT_FALSE(server.empty());

    messages.send(test_chat_id, "photos::get_messages_upload_server tests passed");
}

TEST(photos, get_chat_upload_server)
{
    vk::error_code errc;
    vk::method::photos photos(errc);
    vk::method::messages messages(errc, vk::method::messages::disable_mentions);

    std::string server = photos.get_chat_upload_server(test_chat_id, /*crop=*/512);

    ASSERT_FALSE(server.empty());

    messages.send(test_chat_id, "photos::get_chat_upload_server tests passed");
}

TEST(utils, get_short_link)
{
    vk::error_code errc;
    vk::method::utils utils(errc);
    vk::method::messages messages(errc, vk::method::messages::disable_mentions);

    ASSERT_FALSE(utils.get_short_link("https://www.google.com").empty());
    if (errc) { ASSERT_FALSE(true && "Failed to get short link"); }

    const char fuzz_data[] = {
        0x1A, 0x20, 0x0A, 0x30, 0x21
    };

    utils.get_short_link(fuzz_data);
    if (!errc) { ASSERT_FALSE(true && "Error expected"); }

    messages.send(test_chat_id, "utils::get_short_link tests passed");
}

TEST(utils, check_link)
{
    vk::error_code errc;
    vk::method::utils utils(errc);
    vk::method::messages messages(errc, vk::method::messages::disable_mentions);

    ASSERT_TRUE(utils.check_link("https://www.google.com"));

    messages.send(test_chat_id, "utils::check_link tests passed");
}

TEST(utils, resolve_screen_name)
{
    vk::error_code errc;
    vk::method::utils utils(errc);
    vk::method::messages messages(errc, vk::method::messages::disable_mentions);

    ASSERT_EQ(utils.resolve_screen_name("mm512_mask_gf2p8affineinv_epi64"), 499047616);

    messages.send(test_chat_id, "utils::resolve_screen_name tests passed");
}

int main(int argc, char* argv[])
{
    std::ofstream("config.json") << sample_config;

    vk::config::load("config.json");

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
