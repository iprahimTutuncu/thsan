#include "Game.h"
#include "log.h"
#include "SDL.h"

namespace Thsan {


	Game::Game()
	{
	}

	Game::~Game()
	{	
	}

	bool Game::init()
	{
		logManager.init();
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

		return true;
	}

	void Game::run() {

		if (init()) {
			while (window.isRunning()) {
				window.pollEvent();
				window.update();
			}

			window.close();
		}

	}

	bool Game::close()
	{
		logManager.close();
		SDL_Quit();
		return true;
	}

	void Game::getInfo()
	{
		TS_CORE_TRACE("ThsanEngine v{}.{}", 0, 1);
	}

}