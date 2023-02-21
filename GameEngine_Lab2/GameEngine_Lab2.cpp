#include "Level.h"
#include "GameController.h"

int main()
{
	//GameController::Instance().RunGame();
	Level* l1 = new Level();
	l1->RunLevel();

	return 0;
}

