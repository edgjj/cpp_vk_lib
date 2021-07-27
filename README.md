[![Ubuntu](https://github.com/threadpoolexecutor/cpp_vk_lib/workflows/Ubuntu/badge.svg)](https://github.com/threadpoolexecutor/cpp_vk_lib/actions?query=workflow%3AUbuntu)
[![Windows](https://github.com/threadpoolexecutor/cpp_vk_lib/workflows/Windows/badge.svg)](https://github.com/threadpoolexecutor/cpp_vk_lib/actions?query=workflow%3AWindows)
[![MacOS](https://github.com/threadpoolexecutor/cpp_vk_lib/workflows/MacOS/badge.svg)](https://github.com/threadpoolexecutor/cpp_vk_lib/actions?query=workflow%3AMacOS)
[![CodeFactor](https://www.codefactor.io/repository/github/threadpoolexecutor/cpp_vk_lib/badge/main)](https://www.codefactor.io/repository/github/threadpoolexecutor/cpp_vk_lib/overview/main)
[![BCH compliance](https://bettercodehub.com/edge/badge/threadpoolexecutor/cpp_vk_lib?branch=main)](https://bettercodehub.com/)
[![Documentation](https://img.shields.io/badge/docs-doxygen-blue.svg)](https://threadpoolexecutor.github.io/cpp_vk_lib/index.html)

# cpp_vk_lib
High performance VK API library

## Overview

* Convenient work with API methods
* Attachment handling system
* Built-in multithreading
* Logging
* OAuth-authorization support
* Buttons support

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
#include "cpp_vk_lib/long_poll/api.hpp"
#include "cpp_vk_lib/methods/messages.hpp"

int main()
{
    const std::size_t new_server_interval_secs = 5;
    const std::size_t lp_timeout_secs = 60;

    vk::config::load("/path/to/config.json");
    vk::long_poll::api api(new_server_interval_secs);
    vk::long_poll::data data = api.server();
    vk::method::messages messages(vk::method::messages::disable_mentions);
    while (true)
    {
        for (auto&& event : api.listen(data, lp_timeout_secs))
	{
            api.on_event("message_new", *event, [&event, &messages]{
                auto message_event = event->get_message_event();
                messages.send(message_event.peer_id(), "response");
            });
            api.run();
	}
    }
}

```

## Contributors

* **threadpoolexecutor** - author
* **Sanceilaks** - build under Windows


Please, see `bot` README to find out more info how to create your own bot.
