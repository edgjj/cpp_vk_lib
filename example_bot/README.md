# Example bot

## The common structure of bot:
```
lib_vk.so
bot/
|_ long_poll_api/
|____ long_poll_api
|_ event_handler/
|____ message_new_handler
|____ //* handlers for other event types
|_ commands/
|____ base_command
|____ command1
|____ command2
|_ 3rd_party/
|____ logger
|____ ...
|
bot_build_dir/
|_ config.json
```

So, let's create a simple bot.

## First step: build library

First of all, you have to build library into a shared object.
You can do this with command like this:
```
mkdir build && cd build && qmake .. && make -j8 && g++ -shared -o lib_vk.so *.o && mv lib_vk.so .. && cd .. && rm -rf build
```
, or use already compiled library, which is placed in the root directory.

## Second step: Long Poll API handler

The start point of bot is a long poll listener.

You can check type of incoming event:
```
vk::long_poll_api lp_api;
vk::long_poll_data lp_data;

lp_data = lp_api.get_server();
auto events = lp_api.listen(lp_data);

for (auto&& event : events)
{
	if (event.type() == "message_new") { /* ... */ }
	if (event.type() == "wall_post_new") { /* ... */ }
}
```

## Third step: Event handlers

Next, you should create appropriate inbound handler:

```
class message_event_handler
{
public:
	explicit
	message_event_handler()
	{
		_command_collection.emplace("trigger", std::make_unique<concrete_command_type>());
	}

	void process(const vk::event::message_new& event)
	{
		std::string trigger = event.text().substr(0, event.text().find(' '));

		if (_command_collection.find(trigger) != _command_collection.end())
		{
			_command_collection[trigger]->execute(event);
		}
	}

private:
	std::unordered_map<std::string_view, std::unique_ptr<base_command>> _command_collection;
};
```
, when `base_command` is a common command type.

## Fourth step: Command interface

You can implement command logic in the following way:

```
class base_command
{
	virtual void execute(const vk::event::message_new& event) const = 0;
	virtual ~base_command() = default;
};
```

```
class search_pics_command : public base_command
{
public:
 	void execute(const vk::event::message_new& event) const override
 	{
  		auto photos_list = _photos.search(event.text(), 100);

		if (photos_list.empty())
	{
		_messages.send(event.peer_id(), "No photos found");
    	}
    	else
    	{
      		_messages.send(event.peer_id(), "", photos_list);
    	}
}

private:
    vk::messages _messages;
    vk::photos   _photos;
};
```

## Fifth step: Config file

Next, you should create `config.json` in the bot build directory with the next content:
```
{
	"access_token": "group token",
	"user_token": "user token",
}
```

Note: config file should be placed in the same directory with executable out.

## The final step: Launch :)
