#include "Game.h"
#include "log.h"

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
		return true;
	}

	void Game::run() {
		if(init())
			while (1);
	}

	bool Game::close()
	{
		logManager.close();
		return true;
	}

	void Game::getInfo()
	{
		TS_CORE_TRACE("ThsanEngine v{}.{}", 0, 1);
	}

}