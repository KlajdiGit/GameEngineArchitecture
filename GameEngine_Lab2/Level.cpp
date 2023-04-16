#include "Level.h"
#include "Renderer.h"
#include "TTFont.h"
#include "SpriteSheet.h"
#include "SpriteAnim.h"
#include "Timing.h"
#include "RenderTarget.h"
#include "InputController.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "AudioController.h"
#include "Song.h"
#include "PhysicsController.h"
#include "RigidBody.h"
#include "Player.h"



Level::Level()
{
	AssetController::Instance().Initialize(100000000); //Allocate 100 MB
	Unit::Pool = new ObjectPool<Unit>();
	SoundEffects::Pool = new ObjectPool<SoundEffects>();
	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();

	m_mapSizeX = 0;
	m_mapSizeY = 0;
	m_gameTime = 0.0f;
	m_units.clear();
	m_sdlEvent = { };
	m_input = &InputController::Instance();
	m_quit = false;
	m_level2 = false;
	m_audio = &AudioController::Instance();
	memset(m_effects, 0, sizeof(SoundEffects*) * 2);
	//m_effect = nullptr;
	//m_effectWLD = nullptr;
	m_player1Name = "";
	m_player2Name = "";
	m_song = nullptr;
	m_fArial20 = nullptr;
	m_physics = nullptr;
	m_player = new Player();
	m_player1 = new Player();
	m_timing = &Timing::Instance();

}

Level::~Level()
{
	m_units.clear();
	delete SoundEffects::Pool;
	delete Unit::Pool;
	AssetController::Instance().Clear(); //Free 10MB
	//m_fArial20->Shutdown();
	if (m_player != nullptr)
	{
		delete m_player;
		m_player = nullptr;
	}

	if (m_player1 != nullptr)
	{
		delete m_player1;
		m_player1 = nullptr;
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

void Level::AssignNonDefaultValues()
{
	m_mapSizeX = 128;
	m_mapSizeX = 256;
	m_gameTime = 101.5f;
	for (int count = 0; count < 5; count++)
	{
		Unit* unit = Unit::Pool->GetResource();
		unit->AssignNonDefaultValues();
		m_units.push_back(unit);
	}
	Resource::AssignNonDefaultValues();
}

void Level::Serialize(std::ostream& _stream)
{
	_stream.write(reinterpret_cast<char*>(&m_mapSizeX), sizeof(m_mapSizeX));
	_stream.write(reinterpret_cast<char*>(&m_mapSizeY), sizeof(m_mapSizeY));
	_stream.write(reinterpret_cast<char*>(&m_gameTime), sizeof(m_gameTime));

	int numberOfUnits = m_units.size();
	_stream.write(reinterpret_cast<char*>(&numberOfUnits), sizeof(numberOfUnits));
	for (int count = 0; count < numberOfUnits; count++)
	{
		SerializePointer(_stream, m_units[count]);
	}
	Resource::Serialize(_stream);
}

void Level::Deserialize(std::istream& _stream)
{
	_stream.read(reinterpret_cast<char*>(&m_mapSizeX), sizeof(m_mapSizeX));
	_stream.read(reinterpret_cast<char*>(&m_mapSizeY), sizeof(m_mapSizeY));
	_stream.read(reinterpret_cast<char*>(&m_gameTime), sizeof(m_gameTime));

	int numberOfUnits;
	_stream.read(reinterpret_cast<char*>(&numberOfUnits), sizeof(numberOfUnits));
	for (int count = 0; count < numberOfUnits; count++)
	{
		Unit* unit;
		DeserializePointer(_stream, unit);
		m_units.push_back(unit);
	}
	Resource::Deserialize(_stream);
}

void Level::ToString()
{
	cout << "Level" << endl;
	cout << "MapSizeX:" << m_mapSizeX << endl;
	cout << "MapSizeY:" << m_mapSizeY << endl;
	cout << "GameTime:" << m_gameTime << endl;
	for (int count = 0; count < m_units.size(); count++)
	{
		m_units[count]->ToString();
	}

	Resource::ToString();
}





ofstream writeStream("level.bin", ios::out | ios::binary);
ifstream readStream("level.bin", ios::in, ios::binary);


string temp;
string temp2;
string error;
bool player1 = false;



void Level::HandleInput(SDL_Event _event)
{
	if ((_event.type == SDL_QUIT) ||
		(m_input->KB()->KeyUp(_event, SDLK_ESCAPE)))
	{
		m_quit = true;
	}


	if (player1 == false)
	{
		if ((temp = m_input->KB()->TextInput(_event)) != "")
		{
			m_player1Name += temp;
			error = "";
		}

		else if (m_input->KB()->KeyUp(_event, SDLK_BACKSPACE))
		{

			if (m_player1Name.length() > 0)
			{
				m_player1Name.pop_back();
			}

		}

		else if (m_input->KB()->KeyUp(m_sdlEvent, SDLK_RETURN))
		{
			if (m_player1Name.length() == 0 || m_player1Name.length() > 21)
			{
				error = "Nickname must contain 1 to 20 characters";
			}
			else
				player1 = true;

		}

	}
	else
	{
		if ((temp2 = m_input->KB()->TextInput(_event)) != "")
		{
			m_player2Name += temp2;
			error = "";
		}

		else if (m_input->KB()->KeyUp(_event, SDLK_BACKSPACE))
		{

			if (m_player2Name.length() > 0)
			{
				m_player2Name.pop_back();
			}

		}

		else if (m_input->KB()->KeyUp(m_sdlEvent, SDLK_RETURN))
		{
			if (m_player2Name.length() == 0 || m_player2Name.length() > 21)
			{
				error = "Nickname must contain 1 to 20 characters";
			}
			else {
				//error = "You went to lv 2";
				m_level2 = true;

			}

		}

	}
	m_input->MS()->ProcessButtons(_event);
}



void Level::HandleInputLvTwo(SDL_Event _event)
{
	if ((_event.type == SDL_QUIT) ||
		(m_input->KB()->KeyUp(_event, SDLK_ESCAPE)))
	{
		m_quit = true;
	}

	m_player->HandleInput(_event, m_timing->GetDeltaTime());
	m_input->MS()->ProcessButtons(_event);
}





void Level::RunLevel(Renderer* _renderer)
{
	//Timing* t = &Timing::Instance();
	_renderer->EnumerateDisplayModes();
	_renderer->ChangeDisplayMode(&_renderer->GetResolutions()[0]);





	m_fArial20 = new TTFont();
	m_fArial20->Initialize(40);
	m_song = m_audio->LoadSong("../Assets/Audio/Music/Track1.mp3");
	m_audio->Play(m_song);
	Point ws = _renderer->GetWindowSize();

	SpriteSheet* sheet = SpriteSheet::Pool->GetResource();
	sheet->Load("../Assets/Textures/Background.tga");
	

	while (!m_quit)
	{
		
		m_timing->Tick();

		_renderer->SetDrawColor(Color(255, 255, 255, 255));
		_renderer->ClearScreen();

		while (SDL_PollEvent(&m_sdlEvent) != 0)
		{

			HandleInput(m_sdlEvent);
		}

		_renderer->RenderTexture(sheet, Point{ 0, 0 });
		m_fArial20->Write(_renderer->GetRenderer(), m_player1Name.c_str(), SDL_Color{ 255, 255, 0 }, SDL_Point{ 50, 50 });
		m_fArial20->Write(_renderer->GetRenderer(), m_player2Name.c_str(), SDL_Color{ 255, 255, 0 }, SDL_Point{ 50, 200 });

		m_fArial20->Write(_renderer->GetRenderer(), error.c_str(), SDL_Color{ 255, 0, 0 }, SDL_Point{ 50, 300 });


		std::string guideline;
		guideline = "Quit [ESC] Next Nickname [RETURN] ";
		m_fArial20->Write(_renderer->GetRenderer(), guideline.c_str(), SDL_Color{ 255, 255, 255 }, SDL_Point{ 10, 1050 });


		if (m_level2 == true)
		{
			// call level2
			RunLevel2(_renderer);

		}

		SDL_RenderPresent(_renderer->GetRenderer());
		m_timing->CapFPS();
	}


	delete SpriteAnim::Pool;
	delete SpriteSheet::Pool;
}


void Level::RunLevel2(Renderer* _renderer)
{
	m_audio->Play(m_song);
	m_fArial20->Initialize(20);
	//m_effect = m_audio->LoadEffect("../Assets/Audio/Effects/Whoosh.wav");
	//m_effectWLD = m_audio->LoadEffect("../Assets/Audio/Effects/DistantGunshot.wav");
	m_effects[0] = m_audio->LoadEffect("../Assets/Audio/Effects/Whoosh.wav");
	m_effects[1] = m_audio->LoadEffect("../Assets/Audio/Effects/DistantGunshot.mp3");

	std::string result = "Waiting to start...";
	
	int win = 0, win1 = 0, loss = 0, loss1 = 0;

	while (!m_quit)
	{
		m_timing->Tick();
		_renderer->SetDrawColor(Color(255, 255, 255, 255));
		_renderer->ClearScreen();
	
		m_audio->Play(m_effects[1]);

		while (SDL_PollEvent(&m_sdlEvent) != 0)
		{

			if (m_sdlEvent.type == SDL_KEYDOWN && m_sdlEvent.key.keysym.sym == SDLK_SPACE)
			{
				result = "Rolling...";
				m_audio->Play(m_effects[0]);

			}
			HandleInputLvTwo(m_sdlEvent);
		}


		m_player->Update(m_timing->GetDeltaTime());
		m_player->Render(_renderer, { 20, 30 });

		m_player1->Update(m_timing->GetDeltaTime());
		m_player->Render(_renderer, { 20, 330 });

		//m_audio->Play(m_effectWLD);
		//m_audio->Play(m_effects[1]);

		if (m_player->GetState() == m_player1->GetState())
		{
		}
		else
		{
			if (m_player->GetState() == PlayerState::GetRockState() && m_player1->GetState() == PlayerState::GetScissorState() ||
				m_player->GetState() == PlayerState::GetPaperState() && m_player1->GetState() == PlayerState::GetRockState() ||
				m_player->GetState() == PlayerState::GetScissorState() && m_player1->GetState() == PlayerState::GetPaperState())
			{
				win++;
				loss1++;
			}
			else
			{
				win1++;
				loss++;

			}	
		}

		std::string numWins = "Wins: " + to_string(win);
		std::string numLosses = "Losses: " + to_string(loss);

		std::string numWins1 = "Wins: " + to_string(win1);
		std::string numLosses1 = "Losses: " + to_string(loss1);

		m_fArial20->Write(_renderer->GetRenderer(), m_player1Name.c_str(), SDL_Color{ 0, 255, 0 }, SDL_Point{ 20, 10 });
		m_fArial20->Write(_renderer->GetRenderer(), result.c_str(), SDL_Color{ 255, 0, 0 }, SDL_Point{ 20, 30 });
		m_fArial20->Write(_renderer->GetRenderer(), numWins.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 20, 50 });
		m_fArial20->Write(_renderer->GetRenderer(), numLosses.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 20, 70 });



		m_fArial20->Write(_renderer->GetRenderer(), m_player2Name.c_str(), SDL_Color{ 0, 255, 0 }, SDL_Point{ 20, 310 });
		m_fArial20->Write(_renderer->GetRenderer(), result.c_str(), SDL_Color{ 255, 0, 0 }, SDL_Point{ 20, 330 });
		m_fArial20->Write(_renderer->GetRenderer(), numWins1.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 20, 350 });
		m_fArial20->Write(_renderer->GetRenderer(), numLosses1.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 20, 370 });

		


		SDL_RenderPresent(_renderer->GetRenderer());

	}
}