#pragma once
#include "../core.h"

#include <string>
#include <functional>

namespace Thsan::event {

	enum class type
	{
		None = 0,
		WindowClose,
		WindowResize,
		KeyPressed,
		KeyReleased
	};

	enum class category
	{

	};

}