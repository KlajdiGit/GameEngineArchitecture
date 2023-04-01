#include "GameController.h"
#include "Level.h"


int main()
{
	GameController::Instance().RunGame();
	/*Level* l1 = new Level();
	l1->RunLevel();
	delete l1;*/
	return 0;
}

