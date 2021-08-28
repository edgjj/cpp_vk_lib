#include "cpp_vk_lib/runtime/net/network.hpp"

#include "spdlog/spdlog.h"

#include <curl/curl.h>

bool cpp_vk_lib_curl_verbose;

static std::string escape(std::string_view url)
{
    char* encoded = curl_easy_escape(NULL, url.data(), url.length());
    std::string res{encoded};
    curl_free(encoded);
    return res;
}

static size_t
    string_callback(char* contents, size_t size, size_t nmemb, void* userp)
{
    spdlog::trace(
        "libcurl string callback called, size = {}, nmemb = {}",
        size,
        nmemb);
    (static_cast<std::string*>(userp))->append(contents, size * nmemb);
    return size * nmemb;
}

static size_t
    file_callback(char* contents, size_t size, size_t nmemb, void* stream)
{
    spdlog::trace(
        "libcurl file callback called, size = {}, nmemb = {}",
        size,
        nmemb);
    return fwrite(contents, size, nmemb, reinterpret_cast<FILE*>(stream));
}

static size_t
    buffer_callback(char* contents, size_t size, size_t nmemb, void* userp)
{
    auto vector = static_cast<std::vector<uint8_t>*>(userp);
    spdlog::trace(
        "libcurl buffer callback called, size = {}, nmemb = {}, buffer capacity = {}",
        size,
        nmemb,
        vector->capacity());
    std::copy(contents, contents + (size * nmemb), std::back_inserter(*vector));
    return size * nmemb;
}

static std::string
    create_url(std::string_view host, std::map<std::string, std::string>&& body)
{
    static constexpr size_t average_word_length = 20;
    const size_t estimated_params_length =
        average_word_length * body.size() * 2;
    std::string result;
    result.reserve(host.size() + estimated_params_length);
    result += host;

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

static void set_optional_verbose(CURL* curl) noexcept
{
    if (cpp_vk_lib_curl_verbose) {
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    }
}

namespace runtime {

result<std::string, size_t> network::request(
    std::string_view host,
    std::map<std::string, std::string>&& target)
{
    const std::string url = create_url(host, std::move(target));
    std::unique_ptr<CURL, curl_free_callback> curl_handle{
        curl_easy_init(),
        curl_easy_cleanup};
    CURL* curl = curl_handle.get();
    if (!curl) {
        spdlog::error("curl_easy_init() failed");
        return result<std::string, size_t>(std::string(), -1);
    }
    spdlog::trace("libcurl GET {}", url);
    std::string response;
    response.reserve(100);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, string_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 600L);
    set_optional_verbose(curl);
    if (CURLcode res = curl_easy_perform(curl); res != CURLE_OK) {
        spdlog::error(
            "curl_easy_perform() failed: {}",
            curl_easy_strerror(res));
        return result<std::string, size_t>(std::string(), -1);
    }
    response.shrink_to_fit();
    spdlog::trace("libcurl GET response: {}", response);
    return response;
}

result<std::string, size_t>
    network::request_data(std::string_view host, std::string_view data)
{
    std::unique_ptr<CURL, curl_free_callback> curl_handle{
        curl_easy_init(),
        curl_easy_cleanup};
    CURL* curl = curl_handle.get();
    if (!curl) {
        spdlog::error("curl_easy_init() failed");
        return result<std::string, size_t>(std::string(), -1);
    }

    spdlog::trace("libcurl GET DATA {} {}", host, data);
    std::string response;
    response.reserve(100);
    curl_easy_setopt(curl, CURLOPT_URL, host.data());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, string_callback);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.size());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.data());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 600L);
    set_optional_verbose(curl);
    if (CURLcode res = curl_easy_perform(curl); res != CURLE_OK) {
        spdlog::error(
            "curl_easy_perform() failed: {}",
            curl_easy_strerror(res));
        return result<std::string, size_t>(std::string(), -1);
    }
    response.shrink_to_fit();
    return response;
}

static size_t curl_download_impl(
    void* buffer,
    std::string_view server,
    curl_write_callback write_cb) noexcept(noexcept(write_cb))
{
    std::unique_ptr<CURL, curl_free_callback> curl_handle{
        curl_easy_init(),
        curl_easy_cleanup};
    CURL* curl = curl_handle.get();
    if (!curl) {
        spdlog::error("curl_easy_init() failed");
        return -1;
    }
    curl_easy_setopt(curl, CURLOPT_URL, server.data());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 600L);
    set_optional_verbose(curl);
    if (CURLcode res = curl_easy_perform(curl); res != CURLE_OK) {
        spdlog::error(
            "curl_easy_perform() failed: {}",
            curl_easy_strerror(res));
        return -1;
    }
    return 0;
}

size_t network::download(std::string_view filename, std::string_view server)
{
    spdlog::trace("libcurl download, src: {}, dest: {}", server, filename);
    FILE* fp = fopen(filename.data(), "wb");
    if (!fp) {
        spdlog::error("libcurl: failed to open file {}", filename);
        return -1;
    }
    size_t res = curl_download_impl(fp, server, file_callback);
    fclose(fp);
    return res;
}

size_t network::download(
    std::vector<uint8_t>& buffer,
    std::string_view server,
    size_t estimated_capacity)
{
    spdlog::trace(
        "libcurl download to buffer, reserve capacity: {}",
        estimated_capacity);
    spdlog::trace("libcurl download to buffer, src: {}", server);
    buffer.clear();
    buffer.reserve(estimated_capacity);

    size_t res = curl_download_impl(&buffer, server, buffer_callback);

    buffer.shrink_to_fit();
    spdlog::trace(
        "libcurl successfully downloaded {} bytes from {}",
        buffer.size(),
        server);
    return res;
}

result<std::string, size_t> curl_upload_impl(
    struct curl_httppost* formpost,
    std::string_view server) noexcept(noexcept(string_callback))
{
    std::unique_ptr<CURL, curl_free_callback> curl_handle{
        curl_easy_init(),
        curl_easy_cleanup};
    CURL* curl = curl_handle.get();
    if (!curl) {
        spdlog::error("curl_easy_init() failed");
        curl_formfree(formpost);
        return result<std::string, size_t>(std::string(), -1);
    }
    std::string response;
    response.reserve(100);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, string_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_URL, server.data());
    curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    set_optional_verbose(curl);
    if (CURLcode res = curl_easy_perform(curl); res != CURLE_OK) {
        spdlog::error(
            "curl_easy_perform() failed: {}",
            curl_easy_strerror(res));
        curl_formfree(formpost);
        return result<std::string, size_t>(std::string(), -1);
    }
    curl_formfree(formpost);
    return response;
}

result<std::string, size_t> network::upload(
    std::string_view field_name,
    std::string_view filename,
    std::string_view server,
    std::string_view content_type)
{
    spdlog::trace("libcurl upload Content-Type: {}", content_type);
    spdlog::trace("libcurl upload field: {}", field_name);
    spdlog::trace("libcurl upload, src: {}, dest: {}", filename, server);
    struct curl_httppost* formpost = nullptr;
    struct curl_httppost* lastptr = nullptr;
    // clang-format off
    curl_formadd(&formpost, &lastptr,
        CURLFORM_COPYNAME,    field_name.data(),
        CURLFORM_FILENAME,    filename.data(),
        CURLFORM_FILE,        filename.data(),
        CURLFORM_CONTENTTYPE, content_type.data(),
        CURLFORM_END);
    // clang-format on
    return curl_upload_impl(formpost, server);
}

result<std::string, size_t> network::upload(
    const std::vector<uint8_t>& buffer,
    std::string_view field_name,
    std::string_view server,
    std::string_view content_type)
{
    spdlog::trace("libcurl upload Content-Type: {}", content_type);
    spdlog::trace("libcurl upload field: {}", field_name);
    spdlog::trace(
        "libcurl upload buffer: size: {}, dest: {}",
        buffer.size(),
        server);
    struct curl_httppost* formpost = nullptr;
    struct curl_httppost* lastptr = nullptr;
    // clang-format off
    curl_formadd(&formpost, &lastptr,
        CURLFORM_BUFFER,         "temp",
        CURLFORM_PTRNAME,        "ptr",
        CURLFORM_COPYNAME,       field_name,
        CURLFORM_BUFFERPTR,      buffer.data(),
        CURLFORM_BUFFERLENGTH,   buffer.size(),
        CURLFORM_CONTENTSLENGTH, buffer.size(),
        CURLFORM_CONTENTTYPE,    content_type.data(),
        CURLFORM_END);
    // clang-format on
    auto result = curl_upload_impl(formpost, server);
    if (!result.error()) {
        spdlog::trace(
            "libcurl successfully uploaded {} bytes to {}",
            buffer.size(),
            server);
    }
    return result;
}

}// namespace runtime
