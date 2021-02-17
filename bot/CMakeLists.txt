include_directories(../lib/include)
include_directories(../dependencies/simdjson/include)
include_directories(../dependencies)

set(SOURCES
    commands/base_command.hpp
    commands/docs_search_command.hpp
    commands/keyboard_command.hpp
    commands/hide_keyboard_command.hpp
    commands/on_message_pin_command.hpp
    commands/on_chat_invite_user_command.hpp
    handlers/message_handler.hpp
    long_poller/long_poller.hpp
    utils/string_utils.hpp
    main.cpp
)
add_executable(test ${SOURCES})

target_link_libraries(test -Lbuild cpp_vk_lib pthread curl curlpp -L../dependencies/simdjson simdjson)
