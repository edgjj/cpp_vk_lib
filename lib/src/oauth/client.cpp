#include "oauth/client.hpp"


vk::oauth::client::client(std::string_view username_, std::string_view password_, vk::oauth::device client_type_)
    : client_type(client_type_), username(username_), password(password_)
{
    switch (client_type)
    {
    case device::android:
        target_client_id = android_app_client_id;
        target_client_secret = android_app_client_secret;
        break;
    case device::iphone:
        target_client_id = iphone_app_client_id;
        target_client_secret = iphone_app_client_secret;
        break;
    case device::windows:
        target_client_id = windows_app_client_id;
        target_client_secret = windows_app_client_secret;
        break;
    }
}

std::pair<std::string_view, int64_t> vk::oauth::client::pull()
{
    simdjson::dom::object response =
    parser.parse(net_client.request(std::string(oauth_link) + "token?", {
        {"grant_type", "password"},
        {"client_id",   std::to_string(target_client_id)},
        {"client_secret", target_client_secret},
        {"username",    username.data()},
        {"password",    password.data()}
    }));

    if (error_returned(response, "invalid_client"))
        VK_THROW(vk::exception::access_error, -1, response["error_description"].get_string().take_value().data());

    if (error_returned(response, "invalid_request"))
        VK_THROW(vk::exception::access_error, -1, response["error_description"].get_string().take_value().data());

    if (error_returned(response, "invalid_grant"))
        VK_THROW(vk::exception::access_error, -1, response["error_description"].get_string().take_value().data());

    return {
        response["access_token"].get_string(), response["user_id"].get_int64()
    };
}
