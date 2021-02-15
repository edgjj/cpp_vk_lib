[![Total alerts](https://img.shields.io/lgtm/alerts/g/fragmichwarum/cpp_vk_lib.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/fragmichwarum/cpp_vk_lib/alerts/)

# cpp_vk_lib
Small and simple C++ library to facilitate work with Vkontakte API

## Overview

* Convenient work with API methods
* Attachment handling system
* Built-in multithreading
* Logging
* OAuth-authorization support

## Dependencies
	- curlpp

## Initialize submodules
In `cpp_vk_lib` directory:
```
cd dependencies
cmake .
```
## Build shared object

In `cpp_vk_lib` directory:
```
cmake .
make
```
After that, `.so` library will be available in `build` directory.

## Note

To compile demo bot, please, uncomment this line in `CMakeLists.txt`:
```
add_subdirectory(bot)
```
, and build it from `cpp_vk_lib` directory. Next, place to `build` directory `config.json` with the following content:
```
{
	"access_token": "",
	"user_token": ""
}
```
