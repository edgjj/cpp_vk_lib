# cpp_vk_lib
Small and simple C++ library to facilitate work with Vkontakte API

## Dependencies
	- curlpp

## Build shared object

In `cpp_vk_lib` directory:
```
cmake .
make
```
After that, `.so` library will be available in `shared` directory.

## Note

To compile demo bot, please, uncomment this line in `CMakeLists.txt`:
```
add_subdirectory(bot)
```
, and build it from `cpp_vk_lib` directory. Next, place to `x86_bot` directory `config.json` with the following content:
```
{
	"access_token": "",
	"user_token": ""
}
```
