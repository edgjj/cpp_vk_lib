#include "cpp_vk_lib/runtime/setup_logger.hpp"
#include "cpp_vk_lib/runtime/signal_handlers.hpp"
#include "cpp_vk_lib/vk/config/config.hpp"
#include "cpp_vk_lib/vk/methods/constructor.hpp"
#include "cpp_vk_lib/vk/events/wall_post_new.hpp"
#include "cpp_vk_lib/vk/methods/basic.hpp"

#include "simdjson.h"
#include "spdlog/spdlog.h"

#include <iostream>

inline bool cpp_vk_lib_curl_verbose = true;

int main(int argc, char* argv[])
{
    if (argc != 4) {
        std::cerr << "Usage: ./upload_audio_message <config.json> <file.mp3> <peer_id>" << std::endl;
        return 1;
    }

    const char* config_path = argv[1];
    const char* file_path = argv[2];
    const char* peer_id = argv[3];
    vk::config::load(config_path);
    runtime::setup_signal_handlers();
    runtime::setup_logger(spdlog::level::level_enum::trace);

    const std::string server = vk::method::group_constructor()
        .method("docs.getMessagesUploadServer")
        .param("peer_id", peer_id)
        .param("type", "audio_message")
        .perform_request();
    simdjson::dom::parser parser;
    const std::string upload_server(parser.parse(server)["response"]["upload_url"]);
    const auto upload_response(runtime::network::upload("file", file_path, upload_server));
    if (upload_response.error()) {
        spdlog::error("Upload error: {}", upload_response.error());
    }
    const simdjson::dom::element parsed_upload = parser.parse(upload_response.value());
    const std::string file(parsed_upload["file"]);
    if (file.empty()) {
        return 1;
    }
    const std::string docs_save_response = vk::method::group_constructor()
        .method("docs.save")
        .param("file", file)
        .param("title", "voice")
        .perform_request();
    const simdjson::dom::element uploaded_document = parser.parse(docs_save_response);
    const simdjson::dom::element audio_message = uploaded_document["response"]["audio_message"];
    const std::shared_ptr<vk::attachment::audio_message> doc =
        std::make_shared<vk::attachment::audio_message>(
            audio_message["owner_id"].get_int64(),
            audio_message["id"].get_int64(),
            audio_message["link_ogg"].get_string(),
            audio_message["link_mp3"].get_string());
    vk::method::messages::send(std::stol(peer_id), "", { doc });
    return 0;
}
