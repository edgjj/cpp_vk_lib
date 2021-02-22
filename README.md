![CMake](https://github.com/fragmichwarum/cpp_vk_lib/workflows/CMake/badge.svg)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/fragmichwarum/cpp_vk_lib.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/fragmichwarum/cpp_vk_lib/alerts/)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/fragmichwarum/cpp_vk_lib.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/fragmichwarum/cpp_vk_lib/context:cpp)

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

## Build shared object

In `cpp_vk_lib` directory:
```
cmake .
cmake --build .
```
After that, `.so` library will be available in `build` directory.

## Demo bot

To compile demo bot, please, uncomment this line in `CMakeLists.txt`:
```
add_subdirectory(bot)
```
, and build it from `cpp_vk_lib` directory.
Next, place to `build` directory `config.json` with the following content:
```
{
	"api_keys": {
		"access_token": "",
		"user_token": ""
	},
	"environment": {
		"error_logpath": "/tmp/errors.log",
		"event_logpath": "/tmp/events.log"
	},
	"num_threads": 8
}
```
## Note

Constructive crticism is welcomed, pull requests are welcomed.
