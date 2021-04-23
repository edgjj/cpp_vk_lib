#ifndef BOT_BASE_COMMAND_H
#define BOT_BASE_COMMAND_H


namespace vk {
namespace event {
class message_new;
}// namespace event
}// namespace vk

namespace bot {
namespace command {

class base
{
public:
    virtual void execute(const vk::event::message_new& event) const = 0;
    virtual ~base() = default;
};

}// namespace command
}// namespace bot

#endif// BOT_BASE_COMMAND_H
