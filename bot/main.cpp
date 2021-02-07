#include <algorithm>
#include <unordered_map>

#include "api/long_poll_api.hpp"
#include "methods/messages.hpp"
#include "methods/photos.hpp"

#include "../dependencies/logger/logger.hpp"


class base_command
{
public:
    virtual std::string_view trigger() const noexcept = 0;
    virtual void execute(const vk::event::message_new& event) = 0;
    virtual ~base_command() = default;
};

class repeat_command final : public base_command
{
public:
    std::string_view trigger() const noexcept override
    {
        return "repeat";
    }
    void execute(const vk::event::message_new& event) override
    {
        messages.send(event.peer_id(), "first cmd with arg: " + std::string(event.text()));
    }

private:
    vk::messages messages;
};

class picture_command final : public base_command
{
public:
    std::string_view trigger() const noexcept override
    {
        return "pic";
    }
    void execute(const vk::event::message_new& event) override
    {
        vk::photos photos;
        vk::attachment::attachments_t media = photos.search(event.text(), 25);

        (media.empty())
            ? messages.send(event.peer_id(), "no docs")
            : messages.send(event.peer_id(), "docs: ", media);
    }

private:
    vk::messages messages;
    vk::photos photos;
};

class message_new_handler
{
public:
    using event_wrapper = std::function<void(const vk::event::message_new&)>;

    void on_command(std::string_view trigger, event_wrapper function)
    {
        commands.emplace(trigger, function);
    }
    void try_execute(std::string_view trigger, const vk::event::message_new& event)
    {
        commands.at(trigger)(event);
    }
    void see_contents()
    {
        for (auto&& command : commands)
        {
            logger(logflag::debug | logflag::green) << "loaded command: " << command.first;
        }
        logger(logflag::debug | logflag::green) << "total commands: " << commands.size();
    }

private:
    std::unordered_map<std::string_view, event_wrapper> commands;
};

void init_commands(std::vector<std::unique_ptr<base_command>>&& commands, message_new_handler& message_handler)
{
    for (auto& command : commands)
    {
        message_handler.on_command(command->trigger(), [&](const vk::event::message_new& event){
            logger(logflag::info | logflag::purple) << "message " << event.text();
            command->execute(event);
        });
    }
}

int main()
{
    vk::long_poll_api long_poll;
    vk::long_poll_data long_poll_data = long_poll.server();
    vk::messages messages;
    vk::photos photos;
    message_new_handler message_handler;
    std::vector<std::unique_ptr<base_command>> commands;

    commands.emplace_back(std::make_unique<repeat_command>());
    commands.emplace_back(std::make_unique<picture_command>());

    init_commands(std::move(commands), message_handler);
    message_handler.see_contents();

    while (true)
    {
        auto events = long_poll.listen(long_poll_data);
        std::for_each(std::begin(events), std::end(events), [&](auto& common_event){
            if (common_event->on_type("message_new"))
            {
                long_poll.queue([e = common_event->get_message_event(), &message_handler]{
                    message_handler.try_execute(e.text(), e);
                });
            }
            long_poll_data.ts = common_event->ts();
        });
        long_poll.run();
    }
    return 0;
}
