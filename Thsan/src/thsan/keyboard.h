#pragma once
#include "core.h"
#include "key_code.h"

namespace Thsan {

	bool THSAN_API key(int keyVal);
	bool THSAN_API key_down(int keyVal);
	bool THSAN_API key_up(int keyVal);

	class Keyboard {
	public:
		static void init();
		static void update();

		static bool key(int keyVal);
		static bool keyDown(int keyVal);
		static bool keyUp(int keyVal);
	private:
        constexpr static const int keyCount = 291; //SDL support up to index 290

        static std::array<bool, keyCount> keys;
        static std::array<bool, keyCount> keysDown;
        static std::array<bool, keyCount> keysUp;
	};
}
