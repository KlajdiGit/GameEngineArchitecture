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
#include "Timing.h"
#include "SpriteAnim.h"
#include "SpriteSheet.h"




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
	m_kPos = {0,0};
	
	//m_right = true;
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

//void GameController::HandleInput(SDL_Event _event)
//{
//	string temp;
//	if ((m_sdlEvent.type == SDL_QUIT) ||
//		(m_input->KB()->KeyUp(m_sdlEvent, SDLK_ESCAPE)))
//	{
//		m_quit = true;
//	}
//	else if (m_input->KB()->KeyDown(m_sdlEvent, SDLK_UP))
//	{
//		m_kPos.Y -= 100 * Timing::Instance().GetDeltaTime();
//	}
//	else if (m_input->KB()->KeyDown(m_sdlEvent, SDLK_DOWN))
//	{
//		m_kPos.Y += 100 * Timing::Instance().GetDeltaTime();
//	}
//	else if (m_input->KB()->KeyDown(m_sdlEvent, SDLK_LEFT))
//	{
//		m_kPos.X -= 100 * Timing::Instance().GetDeltaTime();
//	}
//	else if (m_input->KB()->KeyDown(m_sdlEvent, SDLK_RIGHT))
//	{
//		m_kPos.X += 100 * Timing::Instance().GetDeltaTime();
//	}
//	
//	m_input->MS()->ProcessButtons(_event);
//}

void GameController::HandleInput(SDL_Event _event)
{
	string temp;
	if ((_event.type == SDL_QUIT) ||
		(m_input->KB()->KeyUp(_event, SDLK_ESCAPE)))
	{
		m_quit = true;
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_UP))
	{
		m_kPos.y = -100;
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_DOWN))
	{
		m_kPos.y = 100;
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_LEFT))
	{
		m_kPos.x = -100;
		//m_right = false;
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_RIGHT))
	{
		m_kPos.x = 100;
	}
	else
		m_kPos = { 0,0 };
	m_input->MS()->ProcessButtons(_event);
}



void GameController::RunGame()
{
	Initialize();
	Timing* t = &Timing::Instance();
	m_renderer->EnumerateDisplayModes();
	m_renderer->ChangeDisplayMode(&m_renderer->GetResolutions()[0]);

	TTFont* font = new TTFont();
	font->Initialize(20);

	Point ws = m_renderer->GetWindowSize();

	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
	SpriteSheet* sheet = SpriteSheet::Pool->GetResource();
	sheet->Load("../Assets/Textures/Warrior.tga");
	sheet->SetSize(17, 6, 69, 44);
	sheet->AddAnimation(EN_AN_IDLE, 0, 6, 6.0f);

	SpriteSheet* sheet2 = SpriteSheet::Pool->GetResource();
	sheet2->Load("../Assets/Textures/Warrior.tga");
	sheet2->SetSize(17, 6, 69, 44);
	sheet2->AddAnimation(EN_AN_RUN, 6, 8, 6.0f);

	int posX = 1;
	int posY = 1;
	
	

	while (!m_quit)
	{
		//TTFont* font = new TTFont();
		m_renderer->SetDrawColor(Color(255, 255, 255, 255));
		m_renderer->ClearScreen();

		while (SDL_PollEvent(&m_sdlEvent) != 0)
		{
			HandleInput(m_sdlEvent);
		}

		

		

		
		t->Tick();

		posX += m_kPos.x * t->GetDeltaTime();
		posY += m_kPos.y * t->GetDeltaTime();
		//int away = rand() % 150;

		for (int i = 0; i < 10; i++) {
			unsigned int away = rand() % 251;
			//m_rect[i] = Rect{ ws.X /2 + posX + away, ws.Y / 2 + posY + away, ws.X / 2 + posX +  away + 69 * 1.25, ws.Y / 2 + posY + away + 44 * 1.25 };
			
			m_rect[i] = Rect{ static_cast<unsigned int>(ws.X / 2 + posX + away), static_cast<unsigned int>(ws.Y / 2 + posY + away),
				static_cast<unsigned int>(ws.X / 2 + posX + away + 69 * 1.25), static_cast<unsigned int>(ws.Y / 2 + posY + away + 44 * 1.25) };


			/*m_rect[i].X2 *= 1.25;
			m_rect[i].Y2 *= 1.25;*/
			m_renderer->RenderTexture(sheet, sheet->Update(EN_AN_IDLE, t->GetDeltaTime()), m_rect[i]);

		}

		/*for (int i = 0; i < 10; i++) {
			m_renderer->RenderTexture(sheet, sheet->Update(EN_AN_IDLE, t->GetDeltaTime()), m_rect[i]);
		}*/
		

		if (m_kPos.x == 0 && m_kPos.y == 0)
		m_renderer->RenderTexture(sheet, sheet->Update(EN_AN_IDLE, t->GetDeltaTime()), Rect(ws.X / 2 + posX, ws.Y / 2 + posY,
			                                            ws.X / 2 + posX + 69 * 1.25 , ws.Y / 2 + posY + 44 * 1.25));
		else
		{
			if (m_kPos.x == -100)
				m_renderer->RenderTexture(sheet2, sheet2->Update(EN_AN_RUN, t->GetDeltaTime()), Rect(ws.X / 2 + posX + 69 * 1.25, ws.Y / 2 + posY,
					ws.X / 2 + posX , ws.Y / 2 + posY + 44 * 1.25));
			else
				m_renderer->RenderTexture(sheet2, sheet2->Update(EN_AN_RUN, t->GetDeltaTime()), Rect(ws.X / 2 + posX, ws.Y / 2 + posY,
					ws.X / 2 + posX + 69 * 1.25, ws.Y / 2 + posY + 44 * 1.25));

		}

		std::string guide = "[D]ecrease speed [I]ncrease speed [S]ave [L]oad [ESC] Quit ";

		font->Write(m_renderer->GetRenderer(), guide.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 0, 0 });

		std::string speed;
		if( m_kPos.x != 0 || m_kPos.y != 0)
		    speed = "Player Speed: " + to_string(abs((static_cast<int>(m_kPos.x + m_kPos.y))));
		else
		    speed = "Player Speed: ";

		font->Write(m_renderer->GetRenderer(), speed.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 0, 20 });

		std::string enemySpeed = "Enemy Speed: ";
		font->Write(m_renderer->GetRenderer(), enemySpeed.c_str(), SDL_Color{ 0, 255, 0 }, SDL_Point{ 0, 40 });

		std::string enemyTag = "Enemies tagged: ";
		font->Write(m_renderer->GetRenderer(), enemyTag.c_str(), SDL_Color{ 0, 255, 0 }, SDL_Point{ 0, 60 });


		SDL_RenderPresent(m_renderer->GetRenderer());
		t->CapFPS();
	}
	delete SpriteAnim::Pool;
	delete SpriteSheet::Pool;
	font->Shutdown();
	//m_renderer->ShutDown();
}







