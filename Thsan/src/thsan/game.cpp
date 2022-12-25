#include "pch.h"
#include "Game.h"
#include "log.h"
#include "keyboard.h"
#include "SDL.h"

namespace Thsan {


	Game::Game():
		isInit{false}
	{
	}

	Game::~Game()
	{	
	}

	bool Game::init()
	{
		TS_CORE_ASSERT(!isInit, "Game is already initialized, attemp of calling Game::init() more than once is a bad idea, call Game::close() before if you really need to frl.");
		if (!isInit) {
			logManager.init();
			Keyboard::init();
			getInfo();

			if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
				TS_CORE_ERROR("error initiliazing SDL2: {}", SDL_GetError());
				return false;
			}

			SDL_version version;
			SDL_VERSION(&version);
			TS_CORE_TRACE("SDL {}.{}.{}", version.major, version.minor, version.patch);

			if (!window.create())
				return false;

			isInit = true;
		}

		return true;
	}

	void Game::run() {
		if (init()) {
			while (window.isRunning()) {
				window.pollEvent();
				window.update();
				Keyboard::update();
			}

			window.close();
		}

	}

	bool Game::close()
	{
		logManager.close();
		SDL_Quit();
		isInit = false;
		return true;
	}

	void Game::getInfo()
	{
		TS_CORE_TRACE("ThsanEngine v{}.{}", 0, 1);
	}

}