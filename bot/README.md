## How to create your own bot

# Preparation
```
mkdir example_bot
cd example_bot
git clone https://github.com/duonumerouno/cpp_vk_lib.git
```

Of cource, you can add library as a submodule in your project.
Next, you should to create `bot` directory.
Example CMakeLists:
```
include_directories(../cpp_vk_lib/lib/include)
include_directories(../cpp_vk_lib/dependencies/simdjson/include)
include_directories(../cpp_vk_lib/dependencies)

set(SOURCES
    # Your source files.
    main.cpp
)
add_executable(test ${SOURCES})

target_link_libraries(test -Lbuild cpp_vk_lib pthread curl curlpp -L../cpp_vk_lib/dependencies/simdjson simdjson)
```

# Common structure of bot
```
├── CMakeLists.txt
├── commands
│   ├── base.hpp
│   ├── cmd1.hpp
│   ├── cmd2.hpp
│   └── cmd3.hpp
|   └── // ...
├── events
│   ├── on_chat_invite_user.hpp
│   └── on_message_pin.hpp
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

# Creating CMakeLists
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
add_subdirectory(example_bot)
```
