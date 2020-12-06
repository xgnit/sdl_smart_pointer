/*

The order of the APIs are the same as listed in: https://wiki.libsdl.org/CategoryAPI

For each API function an unique ptr and a shared ptr version should be available, unless it's not possible, e.g.
void* can only be written in shared ptr.

All APIs will have the same name of its wrapped brother in SDL, with a prefix of "SP"(smart pointer), and a 
possible suffix of "_U" (unique ptr) or "_S" (shared ptr). If no suffix, there is only the shared ptr version.

License

  SDL Smart Pointer 
  Copyright (C) 1997-2020 Ting Fu <futinn@gmail.com>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
	 claim that you wrote the original software. If you use this software
	 in a product, an acknowledgment in the product documentation would be
	 appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
	 misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

*/

#pragma once


#include <SDL.h>
#include <memory>
#include <string>






namespace SDL_SmartPointer
{
	struct SDL_Deleter
	{
		void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
		void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
		void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
	};




	using SP_SDL_Window = std::unique_ptr<SDL_Window, SDL_Deleter>;
	using SP_SDL_Renderer = std::unique_ptr<SDL_Renderer, SDL_Deleter>;
	using SP_SDL_Texture = std::unique_ptr<SDL_Texture, SDL_Deleter>;

#define SHARED_VOID_2_VOID_PTR(param) (static_cast<void *>(&param))

	
	void SP_SDL_AddEventWatch(SDL_EventFilter filter, std::shared_ptr<void> userdata)
	{
		SDL_AddEventWatch(filter, SHARED_VOID_2_VOID_PTR(userdata));
	}

	void SP_SDL_AddHintCallback(const std::string& name, SDL_HintCallback callback, std::shared_ptr<void> userdata)
	{
		SDL_AddHintCallback(name.c_str(), callback, SHARED_VOID_2_VOID_PTR(userdata));
	}

	SDL_TimerID SP_SDL_AddTimer(Uint32 interval, SDL_TimerCallback callback, std::shared_ptr<void> param)
	{
		return SDL_AddTimer(interval, callback, SHARED_VOID_2_VOID_PTR(param));
	}

	std::unique_ptr<SDL_PixelFormat> SP_SDL_AllocFormat_U(Uint32 pixel_format)
	{
		return std::unique_ptr<SDL_PixelFormat>(SDL_AllocFormat(pixel_format));
	}

	std::shared_ptr<SDL_PixelFormat> SP_SDL_AllocFormat_S(Uint32 pixel_format)
	{
		return std::shared_ptr<SDL_PixelFormat>(SDL_AllocFormat(pixel_format));
	}

	std::shared_ptr<SDL_Palette> SP_SDL_AllocPalette_S(int ncolors)
	{
		return std::shared_ptr<SDL_Palette>(SDL_AllocPalette(ncolors));
	}

	std::unique_ptr<SDL_Palette> SP_SDL_AllocPalette_U(int ncolors)
	{
		return std::unique_ptr<SDL_Palette>(SDL_AllocPalette(ncolors));
	}

	std::shared_ptr<SDL_RWops> SP_SDL_AllocRW_S(void)
	{
		return std::shared_ptr<SDL_RWops> (SDL_AllocRW());
	}

	std::unique_ptr<SDL_RWops> SP_SDL_AllocRW_U(void)
	{
		return std::unique_ptr<SDL_RWops>(SDL_AllocRW());
	}




	/*
	above are the functions that already wrap the raw pointer interfaces
	
	*/



	SP_SDL_Window 
	create_window(char const *title, int x, int y, int w, int h, Uint32 flags)
	{
		return std::unique_ptr<SDL_Window, SDL_Deleter>(
			SDL_CreateWindow(title, x, y, w, h, flags),
			SDL_Deleter());
	}
	/*
	SDL_SmartTexture
		create_texture(std::string pic, unique_ptr<SDL_Renderer, sdl_deleter>& renderer)
	{
		SDL_Surface* tmp_surf = IMG_Load(pic.c_str());
		auto tex = SDL_SmartTexture(
			SDL_CreateTextureFromSurface(renderer.get(), tmp_surf),
			sdl_deleter());
		SDL_FreeSurface(tmp_surf);
		return tex;
	}
	*/

	SP_SDL_Renderer
		create_renderer(std::unique_ptr<SDL_Window, SDL_Deleter>&window)
	{
		return SP_SDL_Renderer(
			SDL_CreateRenderer(window.get(), -1, 0),
			SDL_Deleter());
	}


	void sdl_renderclear(SP_SDL_Renderer& renderer)
	{
		SDL_RenderClear(renderer.get());
	}

	void sdl_rendercopy(SP_SDL_Renderer& renderer, SP_SDL_Texture& tex, std::unique_ptr<SDL_Rect>& src, std::unique_ptr<SDL_Rect>& dest)
	{
		SDL_RenderCopy(renderer.get(), tex.get(), src.get(), dest.get());
	}

	void sdl_rendercopy(SP_SDL_Renderer& renderer, SP_SDL_Texture& tex, std::nullptr_t src, std::unique_ptr<SDL_Rect>& dest)
	{
		SDL_RenderCopy(renderer.get(), tex.get(), NULL, dest.get());
	}

	void sdl_rendercopy(SP_SDL_Renderer& renderer, SP_SDL_Texture& tex, std::unique_ptr<SDL_Rect>& src, std::nullptr_t dest)
	{
		SDL_RenderCopy(renderer.get(), tex.get(), src.get(), NULL);
	}

	void sdl_renderpresent(SP_SDL_Renderer& renderer)
	{
		SDL_RenderPresent(renderer.get());
	}
};