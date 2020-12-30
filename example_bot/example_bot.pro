TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -Wall -O2 -pedantic

LIBS        += ../lib_vk.so -lcurlpp -lsimdjson
INCLUDEPATH += ../

HEADERS     += \
            commands/base_command.hpp                 \
  commands/download_audio_message_command.hpp \
            commands/search_pics_command.hpp          \
            event_handler/long_poll_api.hpp           \
            event_handler/message_event_handler.hpp   \

SOURCES     += \
            main.cpp
