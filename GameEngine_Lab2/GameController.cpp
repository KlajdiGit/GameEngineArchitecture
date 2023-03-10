#include "GameController.h"
#include "Renderer.h"
#include "SpriteSheet.h"
#include "SpriteAnim.h"
#include "TTFont.h"
#include "Timing.h"
#include <time.h>
#include <cstdlib>
#include "Level.h"

GameController::GameController()
{
	m_sdlEvent = { };
}

GameController::~GameController()
{
}

void GameController::RunGame()
{
	Level* l1 = new Level();
	l1->RunLevel();
	//AssetController::Instance().Initialize(10000000); //Allocate 10MB
	//Renderer* r = &Renderer::Instance();
	//Timing* t = &Timing::Instance();
	//r->Initialize(1200, 1000);  // 1920x1080

	//TTFont* font = new TTFont();
	//font->Initialize(20);

	//Point ws = r->GetWindowSize();

	//SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	//SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
	//SpriteSheet* sheet = SpriteSheet::Pool->GetResource();
	//sheet->Load("../Assets/Textures/Warrior.tga");
	//sheet->SetSize(17, 6, 69, 44);
	//sheet->AddAnimation(EN_AN_RUN, 6, 8, 2.0f);



	//while (m_sdlEvent.type != SDL_QUIT)
	//{
	//	t->Tick();
	//	/*srand(time(0));

	//	unsigned int speed[10];
	//	for (int i = 0; i < 10; i++)
	//	{
	//	  speed[i] = (rand() % 20) + 80;

	//	}*/

	//	SDL_PollEvent(&m_sdlEvent);
	//	r->SetDrawColor(Color(128, 128, 128, 255));
	//	r->ClearScreen();
	//	for (unsigned int count = 0; count < 10; count++)
	//	{

	//		unsigned int yPos = 10 + count * 100;
	//		unsigned int xPos = /*speed[count]*/ 80 * ((SDL_GetTicks() - yPos) / 1000.0f);
	//		//unsigned int  xPos = count * 10;
	//		r->RenderTexture(sheet, sheet->Update(EN_AN_RUN, t->GetDeltaTime()), Rect(xPos, yPos, 69 * 1.8 + xPos, yPos + 44 * 1.8));
	//		if (xPos >= 1200) {
	//			//m_sdlEvent.type = SDL_QUIT;

	//		}

	//	}



		SDL_PollEvent(&m_sdlEvent);

		/*std::string s = "Frame number: " + std::to_string(sheet->GetCurrentClip(EN_AN_IDLE));
		font->Write(r->GetRenderer(), s.c_str(), SDL_Color{ 0, 255, 0 }, SDL_Point{ 250, 50 });

	//	/*r->SetDrawColor(Color(0, 128, 0, 255));
	//	r->ClearScreen();

	//	for (int count2 = 0; count2 < 10; count2++) {
	//		unsigned int yPos = 10 + count2 * 100;
	//		unsigned int xPos = 80 * ((SDL_GetTicks() - yPos) / 1000.0f);
	//		r->RenderTexture(sheet, sheet->Update(EN_AN_RUN, t->GetDeltaTime()), Rect(xPos, yPos, 69 * 1.8 + xPos, yPos + 44 * 1.8));

	//	}*/



	//	std::string s = "Frames Per Second: " + std::to_string(t->GetFPS());
	//	font->Write(r->GetRenderer(), s.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 0, 0 });

	//	s = "Game Time: " + std::to_string(SDL_GetTicks() / 1000);
	//	font->Write(r->GetRenderer(), s.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 250, 0 });

	//	SDL_RenderPresent(r->GetRenderer());
	//}

	//delete SpriteAnim::Pool;
	//delete SpriteSheet::Pool;

	//font->Shutdown();
	//r->Shutdown();
}