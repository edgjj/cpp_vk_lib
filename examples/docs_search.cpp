#include "vk/include/config/loader.hpp"
#include "vk/include/setup_logger.hpp"
#include "vk/include/attachment/attachment.hpp"
#include "vk/include/methods/utility/constructor.hpp"

#include <iostream>
#include <random>
#include <vector>

#include "simdjson.h"

std::vector<vk::attachment::attachment_ptr_t> docs_search(std::string_view query, int32_t count)
{
    std::vector<vk::attachment::attachment_ptr_t> documents;
    const std::string raw_response = vk::method::group_constructor()
        .method("docs.search")
        .param("q", query)
        .param("count", std::to_string(count))
        .perform_request();

    simdjson::dom::parser parser;
    const simdjson::dom::element response = parser.parse(raw_response);
    const simdjson::dom::array items = response["response"]["items"].get_array();
    documents.reserve(items.size());

    if (items.size() == 0) { return {}; }

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, items.size() - 1);
    for (uint8_t i = 0; i < items.size() && i < count; ++i) {
        const size_t index = distribution(generator);
        documents.push_back(std::make_shared<vk::attachment::document>(
            items.at(index)["owner_id"].get_int64(),
            items.at(index)["id"].get_int64(),
            items.at(index)["url"].get_string()));
    }

    return documents;
}

int main(int argc, char* argv[])
{
    if (argc != 4) {
        std::cerr << "Usage: ./docs_search <config.json> <query> <count>" << std::endl;
        return 1;
    }

    const char* query = argv[2];
    const char* count = argv[3];

    vk::config::load(argv[1]);
    vk::setup_logger("info");

    for (const auto& attachment : docs_search(query, std::stoi(count))) {
        spdlog::info("found: {}", attachment->value());
    }
}
