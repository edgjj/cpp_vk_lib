#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

#include <sstream>

#include "net/network_client.hpp"


static std::string escape(std::string_view url) {
  return curlpp::escape(url.data());
}

static size_t file_write(FILE* file, char* ptr, size_t size, size_t nmemb) {
  return fwrite(ptr, size, nmemb, file);
}

static std::string genparams(const std::map<std::string, std::string>& body) {
  std::string result;
  for (const auto&[key, value] : body) {
    result += std::string(key) + '=' + escape(value) + '&';
  }
  return result;
}

std::string vk::network_client::request(std::string_view method, const std::map<std::string, std::string>& params) const {
  std::ostringstream response;
  curlpp::Easy curl_easy;

  std::string url = method.data() + genparams(params);
  debug("HTTP POST:", url);

  curl_easy.setOpt(new curlpp::options::Url(url));
  curl_easy.setOpt(new curlpp::options::WriteStream(&response));
  curl_easy.perform();

  debug("HTTP RESPONSE: ", response.str());

  return response.str();
}

std::string vk::network_client::request_data(std::string_view method, std::string_view data) const {
  std::ostringstream response;
  curlpp::Easy curl_easy;

  debug("HTTP POST:", method.data(), data);

  curl_easy.setOpt(new curlpp::options::Url(method.data()));
  curl_easy.setOpt(new curlpp::options::PostFields(data.data()));
  curl_easy.setOpt(new curlpp::options::PostFieldSize(data.size()));
  curl_easy.setOpt(new curlpp::options::WriteStream(&response));
  curl_easy.perform();

  debug("HTTP RESPONSE: ", response.str());

  return response.str();
}

std::string vk::network_client::unescape(std::string_view text) {
  return curlpp::unescape(text.data());
}

std::size_t vk::network_client::download(std::string_view filename, std::string_view server) const {
  FILE* fp = fopen(filename.data(), "w");
  if (not fp) { return -1; }

  curlpp::Easy curl_easy;

  debug("HTTP download:");
  debug("filename:", filename);
  debug("url:");

  curlpp::options::WriteFunction* writef =
    new curlpp::options::WriteFunction(std::bind(
      &file_write, fp,
      std::placeholders::_1,
      std::placeholders::_2,
      std::placeholders::_3
  ));
  curl_easy.setOpt(writef);
  curl_easy.setOpt(new curlpp::options::Url(server.data()));
  curl_easy.perform();
  fclose(fp);
  return 0;
}

std::string vk::network_client::upload(std::string_view field_name, std::string_view filename, std::string_view server) const {
  std::ostringstream response;
  curlpp::Forms formParts;
  formParts.push_back(new curlpp::FormParts::File(field_name.data(), filename.data()));

  curlpp::Easy curl_easy;

  debug("HTTP upload:");
  debug("filename:", filename);
  debug("server:");

  curl_easy.setOpt(new curlpp::options::Url(server.data()));
  curl_easy.setOpt(new curlpp::options::HttpPost(formParts));
  curl_easy.setOpt(new curlpp::options::WriteStream(&response));
  try {
    curl_easy.perform();
  } catch(curlpp::RuntimeError& re) {
    debug_error("HTTP upload error");
  }

  return response.str();
}

