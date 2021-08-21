#include "cpp_vk_lib/runtime/net/network.hpp"

#include "spdlog/spdlog.h"

#include "curlpp/Easy.hpp"
#include "curlpp/Options.hpp"
#include "curlpp/cURLpp.hpp"

#include <sstream>

static size_t file_write_callback(FILE* file, char* ptr, size_t size, size_t nmemb) noexcept
{
    return fwrite(ptr, size, nmemb, file);
}

static size_t buffer_write_callback(void* userp, char* contents, size_t size, size_t nmemb)
{
    auto vector = reinterpret_cast<std::vector<uint8_t>*>(userp);
    vector->insert(vector->end(), contents, contents + (size * nmemb));
    return size * nmemb;
}

static std::string create_parameters(std::map<std::string, std::string>&& body)
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

    if (!body.empty()) {
        result.pop_back();
    }
    result.shrink_to_fit();
    return result;
}

namespace runtime {

std::string network::request(std::string_view host, std::map<std::string, std::string>&& target)
{
    std::ostringstream response;
    curlpp::Easy curl_easy;

    std::string url = host.data() + create_parameters(std::move(target));

    spdlog::trace("HTTP POST: {}", url);

    curl_easy.setOpt(curlpp::options::Url(url));
    curl_easy.setOpt(curlpp::options::WriteStream(&response));
#ifndef CPP_VK_LIB_CURL_VERBOSE
    curl_easy.setOpt(curlpp::options::Verbose(true));
#endif
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
#ifndef CPP_VK_LIB_CURL_VERBOSE
    curl_easy.setOpt(curlpp::options::Verbose(true));
#endif
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

    spdlog::trace("HTTP download: {}", server);

    auto* write_function =
        new curlpp::options::WriteFunction([fp](auto&& placeholder1, auto&& placeholder2, auto&& placeholder3) {
            return file_write_callback(fp,
                std::forward<decltype(placeholder1)>(placeholder1),
                std::forward<decltype(placeholder2)>(placeholder2),
                std::forward<decltype(placeholder3)>(placeholder3));
        });

    curlpp::Easy curl_easy;
    curl_easy.setOpt(write_function);
    curl_easy.setOpt(curlpp::options::FollowLocation(true));
    curl_easy.setOpt(curlpp::options::Url(server.data()));
#ifndef CPP_VK_LIB_CURL_VERBOSE
    curl_easy.setOpt(curlpp::options::Verbose(true));
#endif
    try {
        curl_easy.perform();
    } catch (curlpp::RuntimeError& re) {
        spdlog::error("HTTP: failed to download");
        fclose(fp);
        return -1;
    }
    fclose(fp);

    return 0;
}

size_t network::download(std::vector<uint8_t>& buffer, std::string_view server)
{
    spdlog::trace("HTTP download: {}", server);

    buffer.clear();
    auto* write_function =
        new curlpp::options::WriteFunction([&buffer](auto&& placeholder1, auto&& placeholder2, auto&& placeholder3) {
            return buffer_write_callback(reinterpret_cast<void*>(&buffer),
                std::forward<decltype(placeholder1)>(placeholder1),
                std::forward<decltype(placeholder2)>(placeholder2),
                std::forward<decltype(placeholder3)>(placeholder3));
        });

    curlpp::Easy curl_easy;
    curl_easy.setOpt(write_function);
    curl_easy.setOpt(curlpp::options::FollowLocation(true));
    curl_easy.setOpt(curlpp::options::Url(server.data()));
#ifndef CPP_VK_LIB_CURL_VERBOSE
    curl_easy.setOpt(curlpp::options::Verbose(true));
#endif

    try {
        curl_easy.perform();
    } catch (curlpp::RuntimeError& re) {
        spdlog::error("HTTP: failed to download");
        return -1;
    }

    buffer.shrink_to_fit();
    spdlog::trace("HTTP: downloaded {} bytes", buffer.size());
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
#ifndef CPP_VK_LIB_CURL_VERBOSE
    curl_easy.setOpt(curlpp::options::Verbose(true));
#endif

    try {
        curl_easy.perform();
    } catch (curlpp::RuntimeError& re) {
        spdlog::trace("HTTP upload error");
    }

    return response.str();
}

std::string network::upload(std::string_view field_name, const std::vector<uint8_t>& buffer, std::string_view server, std::string_view type)
{
    class form_part_data : public curlpp::FormPart
    {
    public:
        form_part_data(const char* name, const std::vector<uint8_t>& buffer)
          : curlpp::FormPart(name)
          , buffer_(buffer) {}

        form_part_data(const char* name, const std::vector<uint8_t>& buffer, const char* type)
          : curlpp::FormPart(name)
          , buffer_(buffer)
          , content_type_(type) {}

        form_part_data* clone() const override
        {
            return new form_part_data(*this);
        }

    private:
        void add(curl_httppost** first, curl_httppost** last) override
        {
            if (content_type_.empty()) {
                curl_formadd(first, last,
                    CURLFORM_BUFFER,            "temp",
                    CURLFORM_PTRNAME,           mName.c_str(),
                    CURLFORM_BUFFERPTR,         buffer_.data(),
                    CURLFORM_BUFFERLENGTH,      buffer_.size(),
                    CURLFORM_CONTENTSLENGTH,    buffer_.size(),
                    CURLFORM_CONTENTTYPE,       "application/octet-stream",
                    CURLFORM_END);
            } else {
                curl_formadd(first, last,
                    CURLFORM_BUFFER,            "temp",
                    CURLFORM_PTRNAME,           mName.c_str(),
                    CURLFORM_BUFFERPTR,         buffer_.data(),
                    CURLFORM_BUFFERLENGTH,      buffer_.size(),
                    CURLFORM_CONTENTSLENGTH,    buffer_.size(),
                    CURLFORM_CONTENTTYPE,       content_type_.c_str(),
                    CURLFORM_END);
            }
        }

        const std::vector<uint8_t>& buffer_;
        const std::string content_type_;
    };

    std::ostringstream response;
    curlpp::Forms form_parts;
    curlpp::Easy curl_easy;

    if (type.empty()) {
        form_parts.push_back(new form_part_data(field_name.data(), buffer));
    } else {
        form_parts.push_back(new form_part_data(field_name.data(), buffer, type.data()));
    }

    spdlog::trace("HTTP upload: buffer {}", buffer.size());

    curl_easy.setOpt(curlpp::options::Url(server.data()));
    curl_easy.setOpt(curlpp::options::HttpPost(form_parts));
    curl_easy.setOpt(curlpp::options::WriteStream(&response));
#ifndef CPP_VK_LIB_CURL_VERBOSE
    curl_easy.setOpt(curlpp::options::Verbose(true));
#endif

    try {
        curl_easy.perform();
    } catch (curlpp::RuntimeError& re) {
        spdlog::trace("HTTP upload error: {}", re.what());
    }

    return response.str();
}

}// namespace runtime
