TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS        += ../../lib_vk/lib_vk.so -lcurlpp -lsimdjson
INCLUDEPATH += ../../lib_vk

HEADERS     += \
            commands/base_command.hpp                 \
            event_handler/long_poll_api.hpp           \
            event_handler/message_event_handler.hpp   \
            commands/command1.hpp                     \
            commands/command2.hpp                     \

SOURCES     += \
            main.cpp
