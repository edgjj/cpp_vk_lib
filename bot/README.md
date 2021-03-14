# How to create your own bot

### Preparation
```
mkdir example_bot
cd example_bot
git clone https://github.com/duonumerouno/cpp_vk_lib.git
```

Of cource, you can add library as a submodule in your project.
Next, you should to create `bot` directory with following `CMakeLists.txt`:
```
include_directories(../cpp_vk_lib/lib/include)
include_directories(../cpp_vk_lib/lib/include/cpp_vk_lib)

file(GLOB_RECURSE SRC "*.hpp" "*.cpp")
add_executable(example_bot ${SRC})
target_link_libraries(example_bot -Lcpp_vk_lib/build cpp_vk_lib pthread curl curlpp -L../cpp_vk_lib/dependencies/simdjson simdjson)
```

### Common structure of bot
```
├── CMakeLists.txt
├── commands
│   ├── base.hpp
│   ├── cmd1.hpp
│   ├── cmd2.hpp
│   └── cmd3.hpp
|   └── // ...
├── events
│   ├── reaction1.hpp
│   └── reaction2.hpp
|   └── // ...
├── handlers
│   └── message_handler.hpp
|   └── // ...
├── long_poller
│   └── long_poller.hpp
├── main.cpp
└── utils
    └── string_utils.hpp
    └── // ...
```

### Creating CMakeLists
Here is example CMake script to make bot and library work together:
```
cmake_minimum_required(VERSION 3.9)

project(example_bot
    DESCRIPTION "C++ vk library"
    LANGUAGES CXX
)

set(CMAKE_C_COMPILER /usr/bin/clang CACHE PATH "" FORCE)
set(CMAKE_CXX_COMPILER /usr/bin/clang++ CACHE PATH "" FORCE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MACOSX_RPATH OFF)
set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../build)
set(EXECUTABLE_OUTPUT_PATH ../build)

add_subdirectory(cpp_vk_lib)
add_subdirectory(bot)
```

### Setup config file
In bot `main` function please type:
```
vk::config::load("/path/to/config.json");
```
Sample config:
```
{
	"api_keys": {
		"access_token": "",
		"user_token": ""
	},
	"environment": {
		"error_logpath": "/path/to/errors.log",
		"event_logpath": "/path/to/events.log"
	},
	"num_threads": 16
}
```

### Design goals

This library follows the OCP principle, to allow user easily add any new features.
