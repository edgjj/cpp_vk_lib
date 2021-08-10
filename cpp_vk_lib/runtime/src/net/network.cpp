#include "runtime/include/net/network.hpp"

#include "spdlog/spdlog.h"

#include "curlpp/Easy.hpp"
#include "curlpp/Options.hpp"
#include "curlpp/cURLpp.hpp"

#include <sstream>

static size_t file_write(FILE* file, char* ptr, size_t size, size_t nmemb)
{
    return fwrite(ptr, size, nmemb, file);
}

static std::string create_parameters(const std::map<std::string, std::string>& body)
{
    static constexpr size_t average_word_length = 20;

    std::string result;
    result.reserve(average_word_length * body.size() * 2);

    for (const auto& [key, value] : body) {
        result += key;
        result += '=';
        result += curlpp::escape(value);
        result += '&';
    }

    return result;
}

namespace runtime {

std::string network::request(std::string_view host, const std::map<std::string, std::string>& target)
{
    std::ostringstream response;
    curlpp::Easy curl_easy;

    std::string url = host.data() + create_parameters(target);

    spdlog::trace("HTTP POST: {}", url);

    curl_easy.setOpt(curlpp::options::Url(url));
    curl_easy.setOpt(curlpp::options::WriteStream(&response));
    curl_easy.perform();

    spdlog::trace("HTTP RESPONSE: {}", response.str());

    return response.str();
}

std::string network::request_data(std::string_view host, std::string_view data)
{
    std::ostringstream response;
    curlpp::Easy curl_easy;

    spdlog::trace("HTTP POST: {}", data);

    curl_easy.setOpt(curlpp::options::Url(host.data()));
    curl_easy.setOpt(curlpp::options::PostFields(data.data()));
    curl_easy.setOpt(curlpp::options::PostFieldSize(data.size()));
    curl_easy.setOpt(curlpp::options::WriteStream(&response));
    curl_easy.perform();

    spdlog::trace("HTTP RESPONSE: {}", response.str());

    return response.str();
}

size_t network::download(std::string_view filename, std::string_view server)
{
    FILE* fp = fopen(filename.data(), "w");
    if (!fp) {
        spdlog::trace("Can't open file: {}", filename.data());
        return -1;
    }

    curlpp::Easy curl_easy;

    spdlog::trace("HTTP download: {}", filename);

    auto* write_function =
        new curlpp::options::WriteFunction([fp](auto&& placeholder1, auto&& placeholder2, auto&& placeholder3) {
            return file_write(fp,
                std::forward<decltype(placeholder1)>(placeholder1),
                std::forward<decltype(placeholder2)>(placeholder2),
                std::forward<decltype(placeholder3)>(placeholder3));
        });

    curl_easy.setOpt(write_function);
    curl_easy.setOpt(curlpp::options::Url(server.data()));
    curl_easy.perform();
    fclose(fp);

    return 0;
}

std::string network::upload(std::string_view field_name, std::string_view filename, std::string_view server)
{
    std::ostringstream response;
    curlpp::Forms form_parts;
    curlpp::Easy curl_easy;

    form_parts.push_back(new curlpp::FormParts::File(field_name.data(), filename.data()));

    spdlog::trace("HTTP upload: {}", filename);

    curl_easy.setOpt(curlpp::options::Url(server.data()));
    curl_easy.setOpt(curlpp::options::HttpPost(form_parts));
    curl_easy.setOpt(curlpp::options::WriteStream(&response));

    try {
        curl_easy.perform();
    } catch (curlpp::RuntimeError& re) {
        spdlog::trace("HTTP upload error");
    }

    return response.str();
}

}// namespace runtime