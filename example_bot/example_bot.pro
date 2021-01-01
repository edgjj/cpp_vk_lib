TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -Wall -O2 -pedantic

LIBS        += ../lib_vk.so -lcurlpp -lsimdjson
INCLUDEPATH += ../

HEADERS     += \
            bot/long_poll_api/long_poll_api.hpp               \
            bot/event_handler/message_event_handler.hpp       \
            bot/commands/base_command.hpp                     \
            bot/commands/download_audio_message_command.hpp   \
            bot/commands/search_pics_command.hpp              \
            bot/3rd_party/logger.hpp                          \

SOURCES     += \
            main.cpp
