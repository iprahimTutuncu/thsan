#pragma once

#include "game.h"
#include "log.h"

#ifdef TS_PLATFORM_WINDOWS
extern Thsan::Game* Thsan::create_game();

int main(int argc, char** argv) {
	auto app = Thsan::create_game();
	app->run();
	delete app;
	return 0;
}

#endif
