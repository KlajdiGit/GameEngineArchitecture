#include "GameController.h"
#include "Renderer.h"
#include "SpriteSheet.h"
#include "SpriteAnim.h"
#include "TTFont.h"
#include "Timing.h"

GameController::GameController()
{
	m_sdlEvent = { };
}

GameController::~GameController()
{
}

void GameController::RunGame()
{
	AssetController::Instance().Initialize(10000000); //Allocate 10MB
	Renderer* r = &Renderer::Instance();
	Timing* t = &Timing::Instance();
	r->Initialize(1220, 1000);  // 1920x1080
	
	TTFont* font = new TTFont();
	font->Initialize(20);
	
	Point ws = r->GetWindowSize();

	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
	SpriteSheet* sheet = SpriteSheet::Pool->GetResource();
	sheet->Load("../Assets/Textures/Warrior.tga");
	sheet->SetSize(17, 6, 69, 44);
	sheet->AddAnimation(EN_AN_RUN, 6, 8, 2.0f);

	

	while (m_sdlEvent.type != SDL_QUIT)
	{
		t->Tick();

		SDL_PollEvent(&m_sdlEvent);
		r->SetDrawColor(Color(128, 128, 128, 255));
		r->ClearScreen();
		for (unsigned int count = 0; count < 10; count++)
		{
			unsigned int yPos = 10 + count * 100;
			r->RenderTexture(sheet, sheet->Update(EN_AN_RUN, t->GetDeltaTime()), Rect(0, yPos, 69 * 1.8, yPos + 44 * 1.8));
			
		}
		

		std::string fps = "Frames Per Second: " + std::to_string(t->GetFPS());
		font->Write(r->GetRenderer(), fps.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 0, 0 });

		SDL_RenderPresent(r->GetRenderer());
	}

	delete SpriteAnim::Pool;
	delete SpriteSheet::Pool;
	
	font->Shutdown();
	r->Shutdown();
}