[![Ubuntu](https://github.com/threadpoolexecutor/cpp_vk_lib/workflows/Ubuntu/badge.svg)](https://github.com/threadpoolexecutor/cpp_vk_lib/actions?query=workflow%3AUbuntu)
[![MacOS](https://github.com/threadpoolexecutor/cpp_vk_lib/workflows/MacOS/badge.svg)](https://github.com/threadpoolexecutor/cpp_vk_lib/actions?query=workflow%3AMacOS)
[![CodeFactor](https://www.codefactor.io/repository/github/threadpoolexecutor/cpp_vk_lib/badge/main)](https://www.codefactor.io/repository/github/threadpoolexecutor/cpp_vk_lib/overview/main)
[![Documentation](https://img.shields.io/badge/docs-doxygen-blue.svg)](https://threadpoolexecutor.github.io/cpp_vk_lib/index.html)

# cpp_vk_lib
High performance VK API library

## Overview

* Multithreaded
* Logging
* OAuth-authorization
* Buttons

## Dependencies
	- curl
	- cmake

## Note for Windows users

You should install libcurl and add it to PATH manually.

## Note

You can extend existing or create new method classes by inheritance to implement needed API methods.
Also, of course, you can make PR.

## Example reply bot

```
#include "vk/include/config/loader.hpp"
#include "vk/include/events/message_new.hpp"
#include "vk/include/long_poll/api.hpp"
#include "vk/include/log_level.hpp"
#include "vk/include/methods/basic.hpp"
#include "vk/include/methods/utility/utility.hpp"

#include <fstream>

constexpr char sample_config[] = R"__(
    {
      "api": {
        "access_token": "token",
        "user_token": "not used here"
      },
      "oauth": {
        "login": "not used here",
        "password": "not used here"
      },
      "environment": {
        "num_workers": 8,
        "log_path": "logs.txt"
      }
    }
)__";

int main()
{
    vk::config::load_string(sample_config);
    vk::log_level::trace();

    vk::long_poll api;
    vk::long_poll_data data = api.server();
    
    while (true) {
        auto events = api.listen(data, /*lp_timeout=*/lp_timeout_secs);

        for (auto& event : events) {
            api.on_event("message_new", event, [&event] {
                vk::event::message_new message_event = event.get_message_new();
                vk::method::messages::send(message_event.peer_id(), "Hello from cpp_vk_lib");
            });
        }
        api.run();
    }
}

```

## TODO

* User Long Poll
* API for chat-bots with Python scripting
* More examples
* Windows build without external dependencies

## Contributors

* **threadpoolexecutor** - author
* **Sanceilaks** - build under Windows


## Examples

[Repo with examples](https://github.com/threadpoolexecutor/example_cpp_vk_bot)
