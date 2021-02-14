#ifndef BOT_BASE_COMMAND_H
#define BOT_BASE_COMMAND_H


namespace vk {
namespace event {
class message_new;
} // namespace event
} // namespace vk

class base_command {
public:
  virtual void execute(const vk::event::message_new& event) = 0;
  virtual ~base_command() = default;
};


#endif // BOT_BASE_COMMAND_H
