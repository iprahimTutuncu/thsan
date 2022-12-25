#include <thsan.h>
#include <thsan/keyboard.h>

class SandBox : public Thsan::Game
{
public:
	SandBox() {

		if(!Thsan::key(TS_INPUT_KEY_B))
			TS_CLIENT_WARN("the input B was not clicked :) ");
	}

	~SandBox() {

	}
};


Thsan::Game* Thsan::create_game() 
{
	return new SandBox();
}