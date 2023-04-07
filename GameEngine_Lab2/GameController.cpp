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



GameController::GameController()
{
	m_quit = false;
	m_sdlEvent = { };
	m_renderer = nullptr;
	m_fArial20 = nullptr;
	m_input = nullptr;
	m_physics = nullptr;
	m_timing = nullptr;
	//m_audio = nullptr;
	//m_effect = nullptr;
	//m_song = nullptr;
	//m_wavDraw = nullptr;
	//memset(m_effects, 0, sizeof(SoundEffects*) * MaxEffectChannels);
	//m_zoomY = 5;
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
	m_physics = &PhysicsController::Instance();
	m_timing = &Timing::Instance();
	//m_audio = &AudioController::Instance();
	//m_wavDraw = new WavDraw();
	//m_effects[0] = m_audio->LoadEffect("../Assets/Audio/Effects/Whoosh.wav");

}

void GameController::ShutDown()
{
	delete m_fArial20;
	//delete m_wavDraw;
}

void GameController::HandleInput(SDL_Event _event)
{
	//string temp;
	if ((m_sdlEvent.type == SDL_QUIT) ||
		(m_input->KB()->KeyUp(_event, SDLK_ESCAPE)))
	{
		m_quit = true;
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_a))
	{
		m_physics->AddParticle(glm::vec2{ 300 + rand() % 400, 200 }, 3 + rand() % 5);
	}
	
	
	m_input->MS()->ProcessButtons(_event);
}

void GameController::RunGame()
{
	Initialize();
	
	while (!m_quit)
	{
		m_timing->Tick();

		m_renderer->SetDrawColor(Color(255, 255, 255, 255));
		m_renderer->ClearScreen();

		while (SDL_PollEvent(&m_sdlEvent) != 0)
		{
			HandleInput(m_sdlEvent);
		}

		m_physics->Update(m_timing->GetDeltaTime());
		for (Particle* p : m_physics->GetParticles())
		{
			m_renderer->SetDrawColor(Color(0, 0, 0, 255));
			m_renderer->RenderPoint(Point{ p->GetPositions().x, p->GetPositions().y });
		}

		m_fArial20->Write(m_renderer->GetRenderer(), ("FPS: " + to_string(m_timing->GetFPS())).c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 10, 10 });
		m_fArial20->Write(m_renderer->GetRenderer(), m_physics->ToString().c_str(), SDL_Color{0, 0, 255}, SDL_Point{120, 10});


		SDL_RenderPresent(m_renderer->GetRenderer());
	}
}







