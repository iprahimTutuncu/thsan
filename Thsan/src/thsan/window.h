#pragma once
#include "core.h"

struct SDL_Window;
namespace Thsan {
	class THSAN_API Window
	{
	public:
		Window();
		~Window();

		bool create();
		bool close();
		bool isRunning();

		void pollEvent();
		void update();
		void quit();
	private:
		bool running{ true };
		SDL_Window* window;
	};
}