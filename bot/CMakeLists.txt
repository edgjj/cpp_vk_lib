include_directories(../lib/include)

set(SOURCES
    src/commands/base.hpp
    src/commands/docs_search.hpp
    src/commands/keyboard.hpp
    src/commands/hide_keyboard.hpp
    src/events/on_message_pin.hpp
    src/events/on_chat_invite_user.hpp
    src/handlers/message_handler.hpp
    src/long_poller/long_poller.hpp
    src/utils/string_utils.hpp
    src/main.cpp
)
add_executable(bot ${SOURCES})

target_link_libraries(bot -Lbuild cpp_vk_lib pthread curl curlpp -L../dependencies/simdjson simdjson)
