# sdl_smart_pointer

I start this project because when I was using sdl2 lib, I find it's annoying that it still has pretty much complete raw point API. So I decided to wrap them up to make a smart pointer API.

Manual: 

1. The order of the APIs are the same as listed in: https://wiki.libsdl.org/CategoryAPI

2. All APIs will have the same name of its wrapped brother in SDL, with a prefix of "SP"(smart pointer)

3. If the original function returns a raw pointer, it will return a unique ptr in this lib

4. If the original function revceives raw pointer, its wrapper should be able to receive shared and unique ptr. With only exception of  void* will be only wrapped with std::shared<void>
