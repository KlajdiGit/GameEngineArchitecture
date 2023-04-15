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
#include "PhysicsController.h"
#include "Timing.h"
#include "SpriteAnim.h"
#include "SpriteSheet.h"
#include "RigidBody.h"
#include "Heroine.h"
#include "Level.h"

//#include "Player.h"


GameController::GameController()
{
	m_quit = false;
	m_sdlEvent = { };
	m_renderer = nullptr;
	m_fArial20 = nullptr;
	m_input = nullptr;
	m_physics = nullptr;
	m_timing = nullptr;
	m_fire = nullptr;
	m_smoke = nullptr;
	m_circle = nullptr;
	m_heroine = nullptr;
	//	m_player = nullptr;

}

GameController::~GameController()
{
	ShutDown();
}

void GameController::Initialize()
{
	AssetController::Instance().Initialize(10000000);
	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
	m_renderer = &Renderer::Instance();
	m_renderer->Initialize();
	m_input = &InputController::Instance();
	m_fArial20 = new TTFont();
	m_fArial20->Initialize(20);
	m_physics = &PhysicsController::Instance();
	m_timing = &Timing::Instance();
	m_lv = new Level();

	m_heroine = new Heroine();
	
	//m_audio = &AudioController::Instance();
	//m_wavDraw = new WavDraw();
	//m_effects[0] = m_audio->LoadEffect("../Assets/Audio/Effects/Whoosh.wav");
	/*SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
	m_fire = SpriteSheet::Pool->GetResource();
	m_fire->Load("../Assets/Textures/Fire.tga");
	m_fire->SetSize(6, 10, 64, 64);
	m_fire->AddAnimation(EN_AN_IDLE, 0, 60, 20.0f);
	m_fire->SetBlendMode(SDL_BLENDMODE_BLEND);

	m_smoke = SpriteSheet::Pool->GetResource();
	m_smoke->Load("../Assets/Textures/Smoke.tga");
	m_smoke->SetSize(5, 6, 128, 128);
	m_smoke->AddAnimation(EN_AN_SMOKE_RISE, 0, 30, 20.0f);
	m_smoke->SetBlendMode(SDL_BLENDMODE_BLEND);

	m_circle = SpriteSheet::Pool->GetResource();
	m_circle->Load("../Assets/Textures/Circle.tga");
	m_circle->SetSize(1, 2, 32, 32);
	m_circle->AddAnimation(EN_AN_IDLE, 0, 1, 0.0f);
	m_circle->SetBlendMode(SDL_BLENDMODE_BLEND);*/

}

void GameController::ShutDown()
{
	if (m_heroine != nullptr)
	{
		delete m_heroine;
		m_heroine = nullptr;
	}
	
	if (m_fArial20 != nullptr)
	{
		delete m_fArial20;
		m_fArial20 = nullptr;
	}

	if (SpriteAnim::Pool != nullptr)
	{
		delete SpriteAnim::Pool;
		SpriteAnim::Pool = nullptr;
	}

	if (SpriteSheet::Pool != nullptr)
	{
		delete SpriteSheet::Pool;
		SpriteSheet::Pool = nullptr;
	}
}

void GameController::HandleInput(SDL_Event _event)
{
	//string temp;
	if ((m_sdlEvent.type == SDL_QUIT) ||
		(m_input->KB()->KeyUp(_event, SDLK_ESCAPE)))
	{
		m_quit = true;
	}
	/*else if (m_input->KB()->KeyDown(_event, SDLK_a))
	{
		glm::vec2 pos = glm::vec2{ 16 + rand() % (1920 - 32), 16 + rand() % (1080 - 32) };
		glm::vec2 dest = glm::vec2{ rand() % 1920, rand() % 1080 };
		glm::vec2 dir = dest - pos;
		dir = glm::normalize(dir) * 200.0f;
		m_physics->AddRigidBody(pos, dir, rand() % 128);
	} */

	m_heroine->HandleInput(_event, m_timing->GetDeltaTime());
	//	m_player->HandleInput(_event, m_timing->GetDeltaTime());

	m_input->MS()->ProcessButtons(_event);
}

void GameController::RunGame()
{
	Initialize();
	m_renderer->EnumerateDisplayModes();
	m_renderer->ChangeDisplayMode(&m_renderer->GetResolutions()[0]);
	m_lv->RunLevel(m_renderer);
	/*while (!m_quit)
	{
		m_timing->Tick();

		m_renderer->SetDrawColor(Color(255, 255, 255, 255));
		m_renderer->ClearScreen();

		while (SDL_PollEvent(&m_sdlEvent) != 0)
		{
			HandleInput(m_sdlEvent);
		}

		m_physics->Update(m_timing->GetDeltaTime());

		m_heroine->Update(m_timing->GetDeltaTime());
		m_heroine->Render(m_renderer); */

		/*Rect r = m_circle->Update(EN_AN_IDLE, m_timing->GetDeltaTime());
		for (RigidBody* b : m_physics->GetBodies())
		{
			auto pos = b->GetPosition();
			m_renderer->RenderTexture(m_circle, r, Rect(pos.x - 16, pos.y - 16, pos.x + 16, pos.y + 16), b->GetMass() + 127);
		}*/

		/*m_renderer->RenderTexture(m_fire, m_fire->Update(EN_AN_IDLE, m_timing->GetDeltaTime()), Rect(300, 200, 400, 300));
		Rect r = m_smoke->Update(EN_AN_SMOKE_RISE, m_timing->GetDeltaTime());
		for (Particle* p : m_physics->GetParticles())
		{
			m_renderer->SetDrawColor(Color(0, 0, 0, 255));
			int size = p->GetCurrentSize() * 100 / 2;
			auto pos = p->GetPosition();
			m_renderer->RenderTexture(m_smoke, r, Rect(pos.x - size, pos.y - size, pos.x + size, pos.y + size), (1.0f - p->GetCurrentSize()) * 255 );
		}*/

		//m_fArial20->Write(m_renderer->GetRenderer(), ("FPS: " + to_string(m_timing->GetFPS())).c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 10, 10 });
		//m_fArial20->Write(m_renderer->GetRenderer(), m_physics->ToString().c_str(), SDL_Color{0, 0, 255}, SDL_Point{120, 10});


		SDL_RenderPresent(m_renderer->GetRenderer());
	}

	//ShutDown();
//}







