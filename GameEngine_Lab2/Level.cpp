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
	m_effect = nullptr;
	m_player1Name = "";
	m_player2Name = "";
	m_song = nullptr;
	m_fArial20 = nullptr;
	m_physics = nullptr;
	m_player = new Player();
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
	m_player->HandleInput(_event, m_timing->GetDeltaTime());
	m_input->MS()->ProcessButtons(_event);
}





Timing* t = &Timing::Instance();


void Level::RunLevel(Renderer* _renderer)
{
	Timing* t = &Timing::Instance();
	_renderer->EnumerateDisplayModes();
	_renderer->ChangeDisplayMode(&_renderer->GetResolutions()[0]);


	TTFont* font = new TTFont();
	font->Initialize(20);


	m_fArial20 = new TTFont();
	m_fArial20->Initialize(40);
	m_song = m_audio->LoadSong("../Assets/Audio/Music/Track1.mp3");
	m_audio->Play(m_song);
	Point ws = _renderer->GetWindowSize();

	SpriteSheet* sheet = SpriteSheet::Pool->GetResource();
	sheet->Load("../Assets/Textures/Background.tga");
	/*SpriteSheet* sheet = SpriteSheet::Pool->GetResource();
	sheet->Load("../Assets/Textures/Warrior.tga");
	sheet->SetSize(17, 6, 69, 44);
	sheet->AddAnimation(EN_AN_IDLE, 0, 6, 6.0f);

	SpriteSheet* sheet2 = SpriteSheet::Pool->GetResource();
	sheet2->Load("../Assets/Textures/Warrior.tga");
	sheet2->SetSize(17, 6, 69, 44);
	sheet2->AddAnimation(EN_AN_RUN, 6, 8, 6.0f);

	SpriteSheet* sheet3 = SpriteSheet::Pool->GetResource();
	sheet3->Load("../Assets/Textures/Warrior.tga");
	sheet3->SetSize(17, 6, 69, 44);
	sheet3->AddAnimation(EN_AN_DEATH, 26, 11, 6.0f);

	m_effect = m_audio->LoadEffect("../Assets/Audio/Effects/Whoosh.wav");

	int posX = 1;
	int posY = 1;

	int posNpcX = 1;
	int posNpcY = 1;
	srand(time(nullptr));

	for (int i = 0; i < 10; i++) {
		int x1 = rand() % 300 - 150;
		int x2 = rand() % 300 - 150;
		m_rect[i] = Rect{ static_cast<unsigned int>(ws.X / 2 + x1 + posNpcX), static_cast<unsigned int>(ws.Y / 2 + x2 + posNpcY),
				static_cast<unsigned int>(ws.X / 2 + x1 + posNpcX + 69 * 1.25), static_cast<unsigned int>(ws.Y / 2 + x2 + posNpcY + 44 * 1.25) };
	} */


	while (!m_quit)
	{
		_renderer->SetDrawColor(Color(255, 255, 255, 255));
		_renderer->ClearScreen();

		while (SDL_PollEvent(&m_sdlEvent) != 0)
		{
			HandleInput(m_sdlEvent);
		}

		m_timing->Tick();
		_renderer->RenderTexture(sheet, Point{ 0, 0 });
		m_fArial20->Write(_renderer->GetRenderer(), m_player1Name.c_str(), SDL_Color{ 255, 255, 0 }, SDL_Point{ 50, 50 });
		m_fArial20->Write(_renderer->GetRenderer(), m_player2Name.c_str(), SDL_Color{ 255, 255, 0 }, SDL_Point{ 50, 200 });

		m_fArial20->Write(_renderer->GetRenderer(), error.c_str(), SDL_Color{ 255, 0, 0 }, SDL_Point{ 50, 300 });


		std::string guideline;
		guideline = "Quit [ESC] Next Nickname [RETURN] ";
		font->Write(_renderer->GetRenderer(), guideline.c_str(), SDL_Color{ 255, 255, 255 }, SDL_Point{ 10, 1050 });


		if (m_level2 == true)
		{
			// call level2
			RunLevel2(_renderer);

		}




		/*posX += m_warriorPos.x * t->GetDeltaTime();
		posY += m_warriorPos.y * t->GetDeltaTime();

		posNpcX += m_npcPos.x * t->GetDeltaTime();
		posNpcY += m_npcPos.y * t->GetDeltaTime();


		Rect warriorRect = Rect{ static_cast<unsigned int>(ws.X / 2 + posX), static_cast<unsigned int>(ws.Y / 2 + posY),
				static_cast<unsigned int>(ws.X / 2 + posX + 69 * 1.25), static_cast<unsigned int>(ws.Y / 2 + posY + 44 * 1.25) };


		if (m_warriorPos.x == 0 && m_warriorPos.y == 0)
			_renderer->RenderTexture(sheet, sheet->Update(EN_AN_IDLE, t->GetDeltaTime()), warriorRect, 0, 0, 255);
		else
		{
			if (m_warriorPos.x < 0)
			{
				warriorRect = Rect{ static_cast<unsigned int>(ws.X / 2 + posX + 69 * 1.25), static_cast<unsigned int>(ws.Y / 2 + posY),
				static_cast<unsigned int>(ws.X / 2 + posX), static_cast<unsigned int>(ws.Y / 2 + posY + 44 * 1.25) };
				_renderer->RenderTexture(sheet2, sheet2->Update(EN_AN_RUN, t->GetDeltaTime()), warriorRect, 0, 0, 255);
			}
			else
				_renderer->RenderTexture(sheet2, sheet2->Update(EN_AN_RUN, t->GetDeltaTime()), warriorRect, 0, 0, 255);

		}



		for (int i = 0; i < 10; i++)
		{

			glm::vec2 playerPos = { warriorRect.X1, warriorRect.Y1 };
			glm::vec2 npcPos = { m_rect[i].X1, m_rect[i].Y1 };

			float distance = glm::length(playerPos - npcPos);


			if (distance < 30)
			{
				double duration = 2.0f;
				double startTime = 0.0f;
				m_audio->Play(m_effect);
				if (m_enemyTagged < 10)
					m_enemyTagged++;

				while (startTime < duration)
				{
					_renderer->RenderTexture(sheet3, sheet3->Update(EN_AN_DEATH, t->GetDeltaTime()), m_rect[i], 255, 0, 0);
					startTime += t->GetDeltaTime();
				}
				m_rect[i].X1 = m_rect[i].X2 = m_rect[i].Y1 = m_rect[i].Y2 = 0;
			}

			if (distance < 140)
			{

				_renderer->RenderTexture(sheet2, sheet2->Update(EN_AN_RUN, t->GetDeltaTime()), m_rect[i], 0, 255, 0);

				glm::vec2 direction = glm::normalize(playerPos - npcPos);

				if (m_warriorPos.y == 0)
				{
					m_rect[i].X1 -= direction.x * posNpcX;
					m_rect[i].X2 -= direction.x * posNpcX;
				}

				if (m_warriorPos.x == 0)
				{
					m_rect[i].Y1 -= direction.x * posNpcX;
					m_rect[i].Y2 -= direction.x * posNpcX;
				}

				m_rect[i].X1 -= direction.x * posNpcX;
				m_rect[i].X2 -= direction.x * posNpcX;
				m_rect[i].Y1 -= direction.y * posNpcY;
				m_rect[i].Y2 -= direction.y * posNpcY;

			}
			else if (distance > 160)
			{


				_renderer->RenderTexture(sheet2, sheet2->Update(EN_AN_RUN, t->GetDeltaTime()), m_rect[i], 0, 255, 0);
				glm::vec2 direction = glm::normalize(playerPos - npcPos);

				if (m_warriorPos.y == 0)
				{
					m_rect[i].X1 += direction.x * posNpcX;
					m_rect[i].X2 += direction.x * posNpcX;
				}

				if (m_warriorPos.x == 0)
				{
					m_rect[i].Y1 += direction.x * posNpcX;
					m_rect[i].Y2 += direction.x * posNpcX;
				}


				m_rect[i].X1 += direction.x * posNpcX;
				m_rect[i].X2 += direction.x * posNpcX;
				m_rect[i].Y1 += direction.y * posNpcY;
				m_rect[i].Y2 += direction.y * posNpcY;
			}
			else
				_renderer->RenderTexture(sheet, sheet->Update(EN_AN_IDLE, t->GetDeltaTime()), m_rect[i], 0, 255, 0);

		}



		std::string guide = "[D]ecrease speed [I]ncrease speed [S]ave [L]oad [ESC] Quit ";
		font->Write(_renderer->GetRenderer(), guide.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 0, 0 });

		std::string speed;
		if (m_warriorPos.x != 0 && m_warriorPos.y != 0)
			speed = "Player Speed: " + to_string(abs((static_cast<int>(max(m_warriorPos.x, m_warriorPos.y)))));

		else if (m_warriorPos.x != 0 || m_warriorPos.y != 0)
			speed = "Player Speed: " + to_string(abs((static_cast<int>(m_warriorPos.x + m_warriorPos.y))));

		else
			speed = "Player Speed: ";

		font->Write(_renderer->GetRenderer(), speed.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 0, 20 });


		std::string enemySpeed;
		if (m_warriorPos.x != 0 || m_warriorPos.y != 0)
			enemySpeed = "Enemy Speed: " + to_string(abs((static_cast<int>(m_speedNpc))));

		else
			enemySpeed = "Enemy Speed: ";

		font->Write(_renderer->GetRenderer(), enemySpeed.c_str(), SDL_Color{ 0, 255, 0 }, SDL_Point{ 0, 40 });


		std::string enemyTag;
		if (m_enemyTagged > 0)
			enemyTag = "Enemies tagged: " + to_string(m_enemyTagged);

		else
			enemyTag = "Enemies tagged: ";
		font->Write(_renderer->GetRenderer(), enemyTag.c_str(), SDL_Color{ 0, 255, 0 }, SDL_Point{ 0, 60 });
		*/

		SDL_RenderPresent(_renderer->GetRenderer());
		m_timing->CapFPS();
	}


	delete SpriteAnim::Pool;
	delete SpriteSheet::Pool;
	font->Shutdown();
}


void Level::RunLevel2(Renderer* _renderer)
{
	
	while (!m_quit)
	{
		m_timing->Tick();
		_renderer->SetDrawColor(Color(255, 255, 255, 255));
		_renderer->ClearScreen();
		m_fArial20->Write(_renderer->GetRenderer(), m_player1Name.c_str(), SDL_Color{ 255, 255, 0 }, SDL_Point{ 50, 50 });
		m_fArial20->Write(_renderer->GetRenderer(), m_player2Name.c_str(), SDL_Color{ 255, 255, 0 }, SDL_Point{ 50, 200 });


		while (SDL_PollEvent(&m_sdlEvent) != 0)
		{
			HandleInput(m_sdlEvent);
		}
		m_physics->Update(m_timing->GetDeltaTime());
		m_player->Update(m_timing->GetDeltaTime());
		m_player->Render(_renderer);

		SDL_RenderPresent(_renderer->GetRenderer());

	}
}