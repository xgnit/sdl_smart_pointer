# sdl_smart_pointer

I start this project because when I was using sdl2 lib, I find it's annoying that it still has pretty much complete raw point API. So I decided to wrap them up to make a smart pointer API.

Manual: 

1. The order of the APIs are the same as listed in: https://wiki.libsdl.org/CategoryAPI

2. For each API function an unique ptr and a shared ptr version should be available, unless it's not possible, e.g. void* can only be written in shared ptr.

3. All APIs will have the same name of its wrapped brother in SDL, with a prefix of "SP"(smart pointer) or a possible suffix of "_U" (unique ptr) or "_S" (shared ptr). If no suffix, there is only the shared ptr version.

Examples:
SDL_AddEventWatch -> SP_SDL_AddEventWatch
SDL_AllocFormat -> SP_SDL_AllocFormat_U
SDL_AllocFormat -> SP_SDL_AllocFormat_S
