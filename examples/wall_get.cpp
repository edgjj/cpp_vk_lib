#include "vk/include/config/loader.hpp"
#include "vk/include/setup_logger.hpp"
#include "vk/include/methods/utility/constructor.hpp"
#include "vk/include/events/wall_post_new.hpp"

#include "simdjson.h"

#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 4) {
        std::cerr << "Usage: ./wall_get <config.json> <group_id> <count of posts> " << std::endl;
        return 1;
    }

    const char* group_id = argv[2];
    const char* posts_to_find = argv[3];

    vk::config::load(argv[1]);
    vk::setup_logger("trace");

    const std::string response = vk::method::user_constructor()
        .method("wall.get")
        .param("owner_id", group_id)
        .param("count", posts_to_find)
        .perform_request();

    simdjson::dom::parser parser;
    const simdjson::dom::element parsed_posts = parser.parse(response);
    const simdjson::dom::array posts = parsed_posts["response"]["items"].get_array();
    for (auto post : posts) {
        auto post_object = vk::event::wall_post_new(post);
    }
}
