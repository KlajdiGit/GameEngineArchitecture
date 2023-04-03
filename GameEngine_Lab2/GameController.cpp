#include "GameController.h"
#include "Renderer.h"
#include "TTFont.h"
#include "InputController.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Controller.h"
#include "AudioController.h"
#include "SoundEffects.h"
#include "Song.h"
#include "WavDraw.h"
#include "Level.h"



GameController::GameController()
{
	m_quit = false;
	m_sdlEvent = { };
	m_renderer = nullptr;
	m_fArial20 = nullptr;
	m_input = nullptr;
	m_audio = nullptr;
	m_effect = nullptr;
	m_song = nullptr;
	m_wavDraw = nullptr;
	memset(m_effects, 0, sizeof(SoundEffects*) * MaxEffectChannels);
	m_zoomY = 5;
	m_lv = nullptr;
}

GameController::~GameController()
{
	ShutDown();
}

void GameController::Initialize()
{
	AssetController::Instance().Initialize(10000000);
	m_renderer = &Renderer::Instance();
	m_renderer->Initialize();
	m_input = &InputController::Instance();
	m_fArial20 = new TTFont();
	m_fArial20->Initialize(20);
	m_audio = &AudioController::Instance();
	m_wavDraw = new WavDraw();
	m_effects[0] = m_audio->LoadEffect("../Assets/Audio/Effects/Whoosh.wav");
	m_lv = new Level();
}

void GameController::ShutDown()
{
	delete m_fArial20;
	delete m_wavDraw;
}

void GameController::HandleInput(SDL_Event _event)
{
	string temp;
	if ((m_sdlEvent.type == SDL_QUIT) ||
		(m_input->KB()->KeyUp(m_sdlEvent, SDLK_ESCAPE)))
	{
		m_quit = true;
	}
	else if (m_input->KB()->KeyUp(m_sdlEvent, SDLK_a))
	{
		m_zoomY += 0.5f;
	}
	else if (m_input->KB()->KeyUp(m_sdlEvent, SDLK_s))
	{
		m_zoomY -= 0.5f;
	}
	
	m_input->MS()->ProcessButtons(_event);
}

void GameController::RunGame()
{
	Initialize();
	
	while (!m_quit)
	{
		//TTFont* font = new TTFont();
		m_renderer->SetDrawColor(Color(255, 255, 255, 255));
		m_renderer->ClearScreen();

		while (SDL_PollEvent(&m_sdlEvent) != 0)
		{
			HandleInput(m_sdlEvent);
		}

		//m_wavDraw->DrawWave(m_effects[0]->GetData(), m_renderer, m_zoomY);
        
		m_lv->RunLevel(m_renderer);

		//AssetController::Instance().Initialize(10000000); //Allocate 10MB
		//Timing* t = &Timing::Instance();
		//r->Initialize(1920, 1080);
		//font->Initialize(20);

		//Point ws = r->GetWindowSize();

		//SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
		//SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
		//SpriteSheet* sheet = SpriteSheet::Pool->GetResource();
		//sheet->Load("../Assets/Textures/Warrior.tga");
		//sheet->SetSize(17, 6, 69, 44);
		//sheet->AddAnimation(EN_AN_RUN, 6, 8, 4.8f);

		//unsigned int xPos = 1;
		//unsigned int saveTime;

		//while (xPos < 1920)
		//{
		//	t->Tick();
		//	srand(time(0)); // part of my idea to randomize the speed

		//	r->SetDrawColor(Color(128, 128, 128, 255));
		//	r->ClearScreen();
		//	for (unsigned int count = 0; count < 10; count++)
		//	{

		//		unsigned int yPos = 10 + count * 100;
		//		// my idea of making randomized speed. Assuming the normal walk speed is ((((int)SDL_GetTicks()) -xPos) /1000)
		//		// which is then multiplied by a speed coefficient 
		//		//xPos = ((rand() % 21) + 80) *((((int)SDL_GetTicks()) -xPos) /1000) ;
		//		// 80 will just be in this case the miniaml speed coefficient
		//		xPos = 80 * (SDL_GetTicks() - xPos) / 1000.0f;

		//		r->RenderTexture(sheet, sheet->Update(EN_AN_RUN, t->GetDeltaTime()), Rect(xPos, yPos, 69 * 1.8 + xPos, yPos + 44 * 1.8));
		//	}




	//		std::string s = "Frames Per Second: " + std::to_string(t->GetFPS());
	//		font->Write(r->GetRenderer(), s.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 0, 0 });

	//		saveTime = SDL_GetTicks() / 1000;

	//		s = "Game Time: " + std::to_string(saveTime);
	//		font->Write(r->GetRenderer(), s.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 250, 0 });
	//		s = "Auto Save: ";
	//		if (saveTime >= 5)
	//		{
	//			ofstream writeStream("level1.bin", ios::out | ios::binary);
	//			Level::Serialize(writeStream);
	//			sheet->Serialize(writeStream);
	//			writeStream.close();
	//			//sheet->Load("level1.bin");

	//			s += " Yes";
	//		}
	//		else {
	//			s += " No";
	//		}
	//		font->Write(r->GetRenderer(), s.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 400, 0 });



	//		SDL_RenderPresent(r->GetRenderer());
	//	}

	//	Level::RunLevel2(saveTime);

	//	delete SpriteAnim::Pool;
	//	delete SpriteSheet::Pool;

	//	font->Shutdown();
	//	r->Shutdown();
	//}

		/*std::string s = "Frames Per Second:  You will make it";
		font->Write(m_renderer->GetRenderer(), s.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 0, 0 });*/

		SDL_RenderPresent(m_renderer->GetRenderer());
	}
		//font->Shutdown();

}







