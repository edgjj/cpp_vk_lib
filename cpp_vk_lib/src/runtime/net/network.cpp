#include "cpp_vk_lib/runtime/net/network.hpp"

#include <curl/curl.h>
//#include "curlpp/Easy.hpp"
//#include "curlpp/Options.hpp"
//#include "curlpp/cURLpp.hpp"
#include "spdlog/spdlog.h"

#include <sstream>
#include <fstream>

bool cpp_vk_lib_curl_verbose;

static std::string escape(std::string_view url)
{
    char* encoded = curl_easy_escape(NULL, url.data(), url.length());
    std::string res{encoded};
    curl_free(encoded);
    return res;
}

static size_t string_write_callback(void* contents, size_t size, size_t nmemb, void* userp)
{
    (static_cast<std::string*>(userp))->append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

static size_t file_write_callback(void* contents, size_t size, size_t nmemb, FILE* stream)
{
    return fwrite(contents, size, nmemb, stream);
}

static size_t buffer_write_callback(char* contents, size_t size, size_t nmemb, void* userp)
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
        result += escape(value);
        result += '&';
    }

    if (!body.empty()) {
        result.pop_back();
    }
    result.shrink_to_fit();
    return result;
}

namespace runtime {

std::string network::request(
    std::string_view host,
    std::map<std::string, std::string>&& target)
{
    const std::string url = host.data() + create_parameters(std::move(target));
    CURL* curl_handle = curl_easy_init();
    if (!curl_handle) {
        return /*implement result with error code*/"";
    }
    std::string response;
    response.reserve(100);
    curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, string_write_callback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "cpp_vk_lib");
    curl_easy_setopt(curl_handle, CURLOPT_TIMEOUT, 600L);
    curl_easy_perform(curl_handle);
    response.shrink_to_fit();
    return response;
}

std::string network::request_data(std::string_view host, std::string_view data)
{
    std::string response;
    response.reserve(100);
    CURL* curl_handle = curl_easy_init();
    if (!curl_handle) {
        return /*implement result with error code*/"";
    }
    curl_easy_setopt(curl_handle, CURLOPT_URL, host.data());
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, string_write_callback);
    curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDSIZE, data.size());
    curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, data.data());
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &response);
    curl_easy_perform(curl_handle);
    return response;
}

size_t network::download(std::string_view filename, std::string_view server)
{
    CURL* curl_handle = curl_easy_init();
    if (!curl_handle) {
        return /*implement result with error code*/-1;
    }
    FILE* fp = fopen(filename.data(), "wb");
    if (!fp) {
        return -1;
    }
    curl_easy_setopt(curl_handle, CURLOPT_URL, server.data());
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, file_write_callback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, fp);
    if (CURLcode res = curl_easy_perform(curl_handle); res != CURLE_OK) {
        spdlog::error("HTTP download failed: {}", curl_easy_strerror(res));
        fclose(fp);
        return -1;
    }
    fclose(fp);
    return 0;
}

size_t network::download(std::vector<uint8_t>& buffer, std::string_view server)
{
    CURL* curl_handle = curl_easy_init();
    if (!curl_handle) {
        return /*implement result with error code*/-1;
    }
    buffer.clear();
    curl_easy_setopt(curl_handle, CURLOPT_URL, server.data());
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, buffer_write_callback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, reinterpret_cast<void*>(&buffer));
    if (CURLcode res = curl_easy_perform(curl_handle); res != CURLE_OK) {
        spdlog::error("HTTP download failed: {}", curl_easy_strerror(res));
        return -1;
    }
    return 0;
}

std::string network::upload(
    std::string_view field_name,
    std::string_view filename,
    std::string_view server,
    std::string_view content_type)
{
    CURL* curl_handle = curl_easy_init();
    if (!curl_handle) {
        return /*implement result with error code*/"";
    }
    CURLcode curl_result;
    struct curl_httppost* formpost = NULL;
    struct curl_httppost* lastptr = NULL;
    std::string response;
    response.reserve(100);

    curl_formadd(
        &formpost,
        &lastptr,
        CURLFORM_COPYNAME, field_name,
        CURLFORM_FILENAME, filename.data(),
        CURLFORM_FILE, filename.data(),
        CURLFORM_CONTENTTYPE, content_type.data(),
        CURLFORM_END);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, string_write_callback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl_handle, CURLOPT_URL, server.data());
    curl_easy_setopt(curl_handle, CURLOPT_HTTPPOST, formpost);
    curl_result = curl_easy_perform(curl_handle);

    if (curl_result != CURLE_OK) {
        return /*implement result with error code*/"";
    }
    curl_formfree(formpost);
    return response;
}

std::string network::upload(
    const std::vector<uint8_t>& buffer,
    std::string_view field_name,
    std::string_view server,
    std::string_view content_type)
{
    CURL* curl_handle = curl_easy_init();
    if (!curl_handle) {
        return /*implement result with error code*/"";
    }
    CURLcode curl_result;
    struct curl_httppost* formpost = NULL;
    struct curl_httppost* lastptr = NULL;
    std::string response;
    response.reserve(100);

    curl_formadd(
        &formpost,
        &lastptr,
        CURLFORM_BUFFER, "temp",
        CURLFORM_PTRNAME, "ptr",
        CURLFORM_COPYNAME, field_name,
        CURLFORM_BUFFERPTR, buffer.data(),
        CURLFORM_BUFFERLENGTH, buffer.size(),
        CURLFORM_CONTENTSLENGTH, buffer.size(),
        CURLFORM_CONTENTTYPE, content_type.data(),
        CURLFORM_END);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, buffer_write_callback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, reinterpret_cast<const void*>(&buffer));
    curl_easy_setopt(curl_handle, CURLOPT_URL, server.data());
    curl_easy_setopt(curl_handle, CURLOPT_HTTPPOST, formpost);
    curl_result = curl_easy_perform(curl_handle);

    if (curl_result != CURLE_OK) {
        return /*implement result with error code*/"";
    }
    curl_formfree(formpost);
    return response;
}

}// namespace runtime
