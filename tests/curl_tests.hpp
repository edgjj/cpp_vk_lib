#include "runtime/include/net/network.hpp"
#include "vk/include/setup_logger.hpp"

#include <gtest/gtest.h>

#include <fstream>

TEST(curl, POST)
{
    try {
        const std::string received = runtime::network::request("https://www.example.com");
        if (received.empty()) {
            ASSERT_FALSE(true);
        } else {
            if (received.find("Example Domain") == std::string::npos) {
                ASSERT_FALSE(true);
            }
        }
    } catch (...) {
        ASSERT_FALSE(true);
    }
}

TEST(curl, download_to_file)
{
    try {
        if (runtime::network::download("file", "https://psv4.userapi.com/c536236/u561321493/docs/d33/14376ccebc45/Korone_Headbob_gif.gif?extra=UlatnP7Dsj1z7s6Zz1RS2muhsVPQI9Fs0DzMbbPzYgLWi2IcQz-hqnngTh2BZ612YrwwfOewAA9FbixszKWrwiTxDiKcf5r_LENuEGnhYMTf1kSvhTnPOIDhLk2gVp2oANjl615iDaYcIp90YkgzDhxp") != 0) {
            FAIL() << "Failed to download to file";
        }
        std::remove("file");
    } catch (std::exception& err) {
        ASSERT_FALSE(true);
    }
}

TEST(curl, download_to_buffer)
{
    try {
        if (std::vector<uint8_t> raw_buffer; runtime::network::download(raw_buffer, "https://psv4.userapi.com/c536236/u561321493/docs/d33/14376ccebc45/Korone_Headbob_gif.gif?extra=UlatnP7Dsj1z7s6Zz1RS2muhsVPQI9Fs0DzMbbPzYgLWi2IcQz-hqnngTh2BZ612YrwwfOewAA9FbixszKWrwiTxDiKcf5r_LENuEGnhYMTf1kSvhTnPOIDhLk2gVp2oANjl615iDaYcIp90YkgzDhxp") != 0) {
            FAIL() << "Failed to download to buffer";
        }
    } catch (std::exception& err) {
        ASSERT_FALSE(true);
    }
}

TEST(curl, download_compare)
{
    try {
        const char url[] = "https://www.example.com";
        runtime::network::download("file", url);
        std::ostringstream ss;
        ss << std::ifstream("file").rdbuf();
        const std::string& streambuf = ss.str();
        std::vector<uint8_t> file_buffer(streambuf.begin(), streambuf.end());

        std::vector<uint8_t> raw_buffer;
        runtime::network::download(raw_buffer, url);

        ASSERT_EQ(file_buffer, raw_buffer);

        std::remove("file");
    } catch (std::exception& err) {
        ASSERT_FALSE(true);
    }
}
