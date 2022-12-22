#include <thsan.h>

class SandBox : public Thsan::Game
{
public:
	SandBox() {
	
	}

	~SandBox() {

	}
};


Thsan::Game* Thsan::create_game() 
{
	return new SandBox();
}