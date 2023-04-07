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
	m_npcPos = { 0, 0 };
	
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
		m_npcPos.y = -60;
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_DOWN))
	{
		m_kPos.y = 100;
		m_npcPos.y = 60;
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_LEFT))
	{
		m_kPos.x = -100;
		m_npcPos.x = -60;
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_RIGHT))
	{
		m_kPos.x = 100;
		m_npcPos.x = 60;
	}
	else {
		m_kPos = { 0, 0 };
		m_npcPos = { 0, 0 };
	}
	m_input->MS()->ProcessButtons(_event);
}



void GameController::RunGame()
{
	Initialize();
	m_renderer->EnumerateDisplayModes();
	m_renderer->ChangeDisplayMode(&m_renderer->GetResolutions()[0]);

	m_lv->RunLevel(m_renderer);



    m_renderer->Shutdown();
}







