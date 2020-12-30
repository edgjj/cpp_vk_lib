# cpp_vk_lib
Small and simple C++ library to facilitate work with Vkontakte API

## Dependencies
	- curlpp
	- simdjson


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

## Note
`examples` - a brief overview of the library's capabilities
`example_bot` - an example of a simple bot using `cpp_vk_lib`