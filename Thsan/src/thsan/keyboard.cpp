
#include "pch.h"
#include "keyboard.h"
#include "log.h"

#include <SDL.h>

namespace Thsan
{
	std::array<bool, Keyboard::keyCount> Keyboard::keys;
	std::array<bool, Keyboard::keyCount> Keyboard::keysDown;
	std::array<bool, Keyboard::keyCount> Keyboard::keysUp;
	
	void Keyboard::init()
	{
		std::fill(keys.begin(), keys.end(), false);
		std::fill(keysDown.begin(), keysDown.end(), false);
		std::fill(keysUp.begin(), keysUp.end(), false);
	}

	void Keyboard::update()
	{
		std::fill(keysDown.begin(), keysDown.end(), false);
		std::fill(keysUp.begin(), keysUp.end(), false);

		const Uint8* state = SDL_GetKeyboardState(nullptr);

		for (int i = TS_INPUT_KEY_FIRST; i < keyCount; i++)
		{
			bool wasDown = keys[i];
			keys[i] = state[i];
			bool isDown = keys[i];

			if (wasDown && !isDown)
				keysUp[i] = true;
			else if (!wasDown && isDown)
				keysDown[i] = true;
		}
	}

	bool Keyboard::key(int keyVal)
	{
		TS_CORE_ASSERT(keyVal >= TS_INPUT_KEY_FIRST && keyVal < keyCount, "Invalid keyboard key!");
		if (keyVal >= TS_INPUT_KEY_FIRST && keyVal < keyCount)
			return keys[keyVal];

		return false;
	}

	bool Keyboard::keyDown(int keyVal)
	{
		TS_CORE_ASSERT(keyVal >= TS_INPUT_KEY_FIRST && keyVal < keyCount, "Invalid keyboard key!");
		if (keyVal >= TS_INPUT_KEY_FIRST && keyVal < keyCount)
			return keysDown[keyVal];

		return false;
	}

	bool Keyboard::keyUp(int keyVal)
	{
		TS_CORE_ASSERT(keyVal >= TS_INPUT_KEY_FIRST && keyVal < keyCount, "Invalid keyboard key!");
		if (keyVal >= TS_INPUT_KEY_FIRST && keyVal < keyCount)
			return keysUp[keyVal];

		return false;
	}

	bool key(int keyVal)
	{
		return Keyboard::key(keyVal);
	}
	bool key_down(int keyVal)
	{
		return Keyboard::keyDown(keyVal);
	}
	bool key_up(int keyVal)
	{
		return  Keyboard::keyUp(keyVal);
	}
}