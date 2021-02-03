#include <simdjson.h>

#include "lib/include/utility/exception.hpp"
#include "lib/include/net/network_client.hpp"
#include "lib/include/methods/audio.hpp"

#include "logger/logger.hpp"


std::string vk::audio::get_upload_server() const
{
    return call("audio.getUploadServer", user_params({ }));
}

void vk::audio::save(std::string_view artist, std::string_view title, std::string_view filename, std::string_view raw_server)
{
    simdjson::dom::object response =
    parser.parse(
        network_client.upload(
            "file",
            filename,
            static_cast<std::string_view>(parser.parse(raw_server)["response"]["upload_url"])
        )
    );

    if (response.at_key("error").is_object())
        VK_THROW(exception::upload_error, -1, "Can't upload file. Maybe is not an mp3 track?");

    call("audio.save", user_params({
        {"server",   std::to_string(static_cast<std::int64_t>(response["server"]))},
        {"audio",    static_cast<std::string>(response["audio"])},
        {"hash",     static_cast<std::string>(response["hash"])},
        {"artist",   artist.data()},
        {"title",    title.data()}
    }));
}
