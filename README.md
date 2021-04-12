![CMake](https://github.com/fragmichwarum/cpp_vk_lib/workflows/CMake/badge.svg)
[![CodeFactor](https://www.codefactor.io/repository/github/threadpoolexecutor/cpp_vk_lib/badge/main)](https://www.codefactor.io/repository/github/threadpoolexecutor/cpp_vk_lib/overview/main)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/fragmichwarum/cpp_vk_lib.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/fragmichwarum/cpp_vk_lib/alerts/)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/fragmichwarum/cpp_vk_lib.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/fragmichwarum/cpp_vk_lib/context:cpp)
[![BCH compliance](https://bettercodehub.com/edge/badge/duonumerouno/cpp_vk_lib?branch=main)](https://bettercodehub.com/)
[![Documentation](https://img.shields.io/badge/docs-doxygen-blue.svg)](https://duonumerouno.github.io/cpp_vk_lib/index.html)

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
	- curlpp

## Run tests

In `cpp_vk_lib` directory:
```
cmake .
cmake --build .
./build/test
```

## Example reply bot

```
#include "cpp_vk_lib/long_poll/api.hpp"
#include "cpp_vk_lib/methods/messages.hpp"

int main() {
  const std::size_t new_server_interval_secs = 5;
  const std::size_t lp_timeout_secs = 60;

  vk::config::load("/path/to/config.json");
  vk::long_poll::api api(new_server_interval_secs);
  vk::long_poll::data data = api.server();
  vk::method::messages messages(vk::method::messages::disable_mentions);
  while (true) {
    for (auto&& event : api.listen(data, lp_timeout_secs)) {
      api.on_event("message_new", *event, [&event, &messages]{
        auto message_event = event->get_message_event();
        messages.send(message_event.peer_id(), "response");
      });
      api.run();
    }
  }
}

```

Please, see `bot` README to find out more info how to create your own bot.
