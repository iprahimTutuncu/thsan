#pragma once
#include "core.h"

namespace Thsan {
	class THSAN_API Game
	{
	public:
		Game();
		virtual ~Game();
		void run();
	};

	Game* create_game();
};