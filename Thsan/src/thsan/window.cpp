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

		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit();
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
