#include "pch.h"
#include "window.h"
#include "SDL.h"
#include "log.h"

namespace Thsan {

	Window::Window(): window(nullptr)
	{

	}

	Window::~Window()
	{
		if (window)
			close();
	}

	bool Window::create()
	{
		window = SDL_CreateWindow("my application", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 728, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		if (!window) {
			TS_CORE_ERROR("Error creating window: {}", SDL_GetError());
			return false;
		}
		return true;
	}
	bool Window::close()
	{
		SDL_DestroyWindow(window);
		window = nullptr;
		return true;
	}
	bool Window::isRunning()
	{
		return running;
	}
	void Window::pollEvent()
	{
		/*
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit();
		}
		*/

		SDL_Event event;

		SDL_PumpEvents();

		while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_QUIT, SDL_WINDOWEVENT) > 0)

		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit();
			case SDL_APP_TERMINATING:
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					//sdl->g_resized = true;
					//sdl->g_new_width = event.window.data1;
					//sdl->g_new_height = event.window.data2;
				}
				break;
			default:
				break;
			}
		}
	}
	void Window::update()
	{
		SDL_UpdateWindowSurface(window);
	}
	void Window::quit()
	{
		running = false;
	}
}

#include "../pch.h"