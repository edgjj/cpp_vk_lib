# cpp_vk_lib
Small and simple C++ library to facilitate work with Vkontakte API

## Set up
Please, create `init.json` file with next content:
```
{
	"token": {
		"access_token": "",
		"user_token": ""
	},
	"group_id": "",
	"api_v": "5.124"
}
```
and fill in your data.

## Examples of the most frequent user cases

### Send a message
```
	long peer_id = 2000000001;
	
	vk::messages messages;
	messages.send(peer_id, "Hello, World!");
```

### Get and listen to Long Poll server
```
	vk::long_poll_api lp_api;
	vk::long_poll_data lp_data;

	lp_data = lp_api.get_server();
	for (const vk::update::common& common_update : lp_api.listen(lp_data))
	{
		if (common_update.type() == "message_new")
		{
			// ...
		}
	}
```

### Upload and send photo to private message
```
	long peer_id = 2000000008;
	
	std::string raw_json = photos.get_messages_upload_server(peer_id);
	
	std::shared_ptr<vk::attachment::photo_attachment> attachment = photos.save_messages_photo("/home/fragmichwarum/cat.jpg", raw_json);
	
	messages.send(peer_id, "Here is your photo: ", { attachment });
```

### Upload audio to user playlist
```
	vk::audio audio;
	
	std::string raw_json = audio.get_upload_server();
	audio.save("Artist", "Name", "/path/to/your/wonderful/music.mp3", raw_json);
	
```
