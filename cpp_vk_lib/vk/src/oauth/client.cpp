#include "vk/include/oauth/client.hpp"

#include "vk/include/exception/exception.hpp"
#include "vk/include/methods/utility/constructor.hpp"

#include "simdjson.h"

vk::oauth::client::client(std::string_view username, std::string_view password, vk::oauth::target_client client_type)
    : client_type_(client_type)
    , username_(username)
    , password_(password)
    , target_client_secret_()
    , target_client_id_()
    , pulled_token_()
    , pulled_user_id_(0)
{
    switch (client_type_) {
        case target_client::android:
            target_client_id_ = context::android_app_client_id;
            target_client_secret_ = context::android_app_client_secret;
            break;
        case target_client::iphone:
            target_client_id_ = context::iphone_app_client_id;
            target_client_secret_ = context::iphone_app_client_secret;
            break;
        case target_client::windows:
            target_client_id_ = context::windows_app_client_id;
            target_client_secret_ = context::windows_app_client_secret;
            break;
    }
    pull();
}

vk::oauth::client::~client() = default;

static bool error_returned(const simdjson::dom::object& response, std::string_view error_desc)
{
    return response.begin().key() == "error" && response["error"].get_string().take_value() == error_desc;
}

void vk::oauth::client::pull()
{
    method::raw_constructor constructor;

    constructor
        .method(std::string(context::oauth_link) + "token?")
        .param("grant_type", "password")
        .param("client_id", std::to_string(target_client_id_))
        .param("client_secret", target_client_secret_)
        .param("username", username_.data())
        .param("password", password_.data());

    simdjson::dom::parser parser;
    const simdjson::dom::object response = parser.parse(constructor.perform_request());

    if (error_returned(response, "invalid_client") || error_returned(response, "invalid_request") ||
        error_returned(response, "invalid_grant")) {
        throw exception::access_error(-1, response["error_description"].get_c_str().take_value());
    }

    pulled_token_ = response["access_token"].get_c_str().take_value();
    pulled_user_id_ = response["user_id"].get_int64();
}

std::string vk::oauth::client::token() const noexcept
{
    return pulled_token_;
}

int64_t vk::oauth::client::user_id() const noexcept
{
    return pulled_user_id_;
}
