#pragma once
#include "core.h"
#include "manager/log_manager.h"
namespace Thsan {
	class THSAN_API Game
	{
	public:
		Game();
		virtual ~Game();
		bool init();
		void run();
		bool close();
		void getInfo();
	private:
		//Managers
		LogManager logManager;
	};

	Game* create_game();
};