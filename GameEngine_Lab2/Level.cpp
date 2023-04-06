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

Level::Level()
{
	AssetController::Instance().Initialize(10000000); //Allocate 10 MB
	Unit::Pool = new ObjectPool<Unit>();
	SoundEffects::Pool = new ObjectPool<SoundEffects>();

	m_mapSizeX = 0;
	m_mapSizeY = 0;
	m_gameTime = 0.0f;
	m_units.clear();
	m_warriorPos = { 0,0 };
	m_npcPos = { 0, 0 };

	m_sdlEvent = { };
	m_input = &InputController::Instance();
	m_quit = false;
	m_audio = &AudioController::Instance();
	m_effect = nullptr;
	//std::vector<Rect> m_rect(10);
	//m_rect.resize(10);



}

Level::~Level()
{
	m_units.clear();
	delete SoundEffects::Pool;
	delete Unit::Pool;
	AssetController::Instance().Clear(); //Free 10MB
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


void Level::HandleInput(SDL_Event _event)
{
	string temp;
	if ((_event.type == SDL_QUIT) ||
		(m_input->KB()->KeyUp(_event, SDLK_ESCAPE)))
	{
		m_quit = true;
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_UP))
	{
		m_warriorPos.y = -100;
		m_npcPos.y = -60;

	}
	else if (m_input->KB()->KeyDown(_event, SDLK_DOWN))
	{
		m_warriorPos.y = 100;
		m_npcPos.y = 60;

	}
	else if (m_input->KB()->KeyDown(_event, SDLK_LEFT))
	{
		m_warriorPos.x = -100;
		m_npcPos.x = -60;
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_RIGHT))
	{
		m_warriorPos.x = 100;
		m_npcPos.x = 60;

	}
	else
	{
		m_warriorPos = { 0,0 };
		m_npcPos = { 0, 0 };
	}
	m_input->MS()->ProcessButtons(_event);
}


void Level::RunLevel(Renderer* _renderer)
{
	Timing* t = &Timing::Instance();
	_renderer->EnumerateDisplayModes();
	_renderer->ChangeDisplayMode(&_renderer->GetResolutions()[0]);

	TTFont* font = new TTFont();
	font->Initialize(20);

	Point ws = _renderer->GetWindowSize();

	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
	SpriteSheet* sheet = SpriteSheet::Pool->GetResource();
	sheet->Load("../Assets/Textures/Warrior.tga");
	sheet->SetSize(17, 6, 69, 44);
	sheet->AddAnimation(EN_AN_IDLE, 0, 6, 6.0f);
	//std::vector<Rect> m_rect;


	SpriteSheet* sheet2 = SpriteSheet::Pool->GetResource();
	sheet2->Load("../Assets/Textures/Warrior.tga");
	sheet2->SetSize(17, 6, 69, 44);
	sheet2->AddAnimation(EN_AN_RUN, 6, 8, 6.0f);


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

		//m_rect.push_back( Rect{ static_cast<unsigned int>(ws.X / 2 + x1 + posNpcX), static_cast<unsigned int>(ws.Y / 2 + x2 + posNpcY),
			//		static_cast<unsigned int>(ws.X / 2 + x1 + posNpcX + 69 * 1.25), static_cast<unsigned int>(ws.Y / 2 + x2 + posNpcY + 44 * 1.25) });

		//std::cout << "x1: " << x1 << " x2: " << x2 << std::endl;
	}



	while (!m_quit)
	{
		_renderer->SetDrawColor(Color(255, 255, 255, 255));
		_renderer->ClearScreen();

		while (SDL_PollEvent(&m_sdlEvent) != 0)
		{
			HandleInput(m_sdlEvent);
		}

		t->Tick();

		posX += m_warriorPos.x * t->GetDeltaTime();
		posY += m_warriorPos.y * t->GetDeltaTime();

		posNpcX += m_npcPos.x * t->GetDeltaTime();
		posNpcY += m_npcPos.y * t->GetDeltaTime();




		Rect warriorRect = Rect{ static_cast<unsigned int>(ws.X / 2 + posX), static_cast<unsigned int>(ws.Y / 2 + posY),
				static_cast<unsigned int>(ws.X / 2 + posX + 69 * 1.25), static_cast<unsigned int>(ws.Y / 2 + posY + 44 * 1.25) };



		if (m_warriorPos.x == 0 && m_warriorPos.y == 0)
			/*m_renderer->RenderTexture(sheet, sheet->Update(EN_AN_IDLE, t->GetDeltaTime()), Rect(ws.X / 2 + posX, ws.Y / 2 + posY,
														ws.X / 2 + posX + 69 * 1.25 , ws.Y / 2 + posY + 44 * 1.25));*/
			_renderer->RenderTexture(sheet, sheet->Update(EN_AN_IDLE, t->GetDeltaTime()), warriorRect, 0, 0, 255);
		else
		{
			if (m_warriorPos.x < 0)
			{
				warriorRect = Rect{ static_cast<unsigned int>(ws.X / 2 + posX + 69 * 1.25), static_cast<unsigned int>(ws.Y / 2 + posY),
				static_cast<unsigned int>(ws.X / 2 + posX), static_cast<unsigned int>(ws.Y / 2 + posY + 44 * 1.25) };
				_renderer->RenderTexture(sheet2, sheet2->Update(EN_AN_RUN, t->GetDeltaTime()), warriorRect, 0, 0, 255);
				/*m_renderer->RenderTexture(sheet2, sheet2->Update(EN_AN_RUN, t->GetDeltaTime()), Rect(ws.X / 2 + posX + 69 * 1.25, ws.Y / 2 + posY,
					ws.X / 2 + posX , ws.Y / 2 + posY + 44 * 1.25));*/
			}


			else
				_renderer->RenderTexture(sheet2, sheet2->Update(EN_AN_RUN, t->GetDeltaTime()), warriorRect, 0, 0, 255);

		}

		/*for (int i = 0; i < 10; i++)
		{

			m_renderer->RenderTexture(sheet, sheet->Update(EN_AN_IDLE, t->GetDeltaTime()), m_rect[i]);

		}*/


		//if (m_npcPos.x < 0)
		//{
		//	m_rect[i] = Rect{ static_cast<unsigned int>(ws.X / 2 + posNpcX + 69 * 1.25), static_cast<unsigned int>(ws.Y / 2 + posNpcY),
		//	static_cast<unsigned int>(ws.X / 2 + posNpcX), static_cast<unsigned int>(ws.Y / 2 + posNpcY + 44 * 1.25) };
		//	m_renderer->RenderTexture(sheet2, sheet2->Update(EN_AN_RUN, t->GetDeltaTime()), m_rect[i], 0, 255, 0);
		//	/*m_renderer->RenderTexture(sheet2, sheet2->Update(EN_AN_RUN, t->GetDeltaTime()), Rect(ws.X / 2 + posX + 69 * 1.25, ws.Y / 2 + posY,
		//		ws.X / 2 + posX , ws.Y / 2 + posY + 44 * 1.25));*/
		//}
		//else
		//	m_renderer->RenderTexture(sheet2, sheet2->Update(EN_AN_RUN, t->GetDeltaTime()), m_rect[i], 0, 255, 0);


		for (int i = 0; i < 10; i++)
		{

			glm::vec2 playerPos = { warriorRect.X1, warriorRect.Y1 };
			glm::vec2 npcPos = { m_rect[i].X1, m_rect[i].Y1 };

			float distance = glm::length(playerPos - npcPos);

			if (distance < 30)
			{
				m_audio->Play(m_effect);
				m_rect[i].X1 = m_rect[i].X2 = m_rect[i].Y1 = m_rect[i].Y2 = 0;
				//m_rect.erase(m_rect.begin() + i);
			}

			if (distance < 140)
			{
				//if (m_npcPos.x < 0)
			 //   {
				//m_rect[i] = Rect{ static_cast<unsigned int>(ws.X / 2 + posNpcX + 69 * 1.25), static_cast<unsigned int>(ws.Y / 2 + posNpcY),
				//static_cast<unsigned int>(ws.X / 2 + posNpcX), static_cast<unsigned int>(ws.Y / 2 + posNpcY + 44 * 1.25) };
				//m_renderer->RenderTexture(sheet2, sheet2->Update(EN_AN_RUN, t->GetDeltaTime()), m_rect[i], 0, 255, 0);
				///*m_renderer->RenderTexture(sheet2, sheet2->Update(EN_AN_RUN, t->GetDeltaTime()), Rect(ws.X / 2 + posX + 69 * 1.25, ws.Y / 2 + posY,
				//	ws.X / 2 + posX , ws.Y / 2 + posY + 44 * 1.25));*/
	   //  		}
		  //   	else
				_renderer->RenderTexture(sheet2, sheet2->Update(EN_AN_RUN, t->GetDeltaTime()), m_rect[i], 0, 255, 0);

				glm::vec2 direction = glm::normalize(playerPos - npcPos);
				m_rect[i].X1 -= direction.x * posNpcX;
				m_rect[i].X2 -= direction.x * posNpcX;
				m_rect[i].Y1 -= direction.y * posNpcY;
				m_rect[i].Y2 -= direction.y * posNpcY;

			}
			else if (distance > 160)
			{

				//if (m_npcPos.x < 0)
				//{
				//	m_rect[i] = Rect{ static_cast<unsigned int>(ws.X / 2 + posNpcX + 69 * 1.25), static_cast<unsigned int>(ws.Y / 2 + posNpcY),
				//	static_cast<unsigned int>(ws.X / 2 + posNpcX), static_cast<unsigned int>(ws.Y / 2 + posNpcY + 44 * 1.25) };
				//	m_renderer->RenderTexture(sheet2, sheet2->Update(EN_AN_RUN, t->GetDeltaTime()), m_rect[i], 0, 255, 0);
				//	/*m_renderer->RenderTexture(sheet2, sheet2->Update(EN_AN_RUN, t->GetDeltaTime()), Rect(ws.X / 2 + posX + 69 * 1.25, ws.Y / 2 + posY,
				//		ws.X / 2 + posX , ws.Y / 2 + posY + 44 * 1.25));*/
				//}
				//else
				_renderer->RenderTexture(sheet2, sheet2->Update(EN_AN_RUN, t->GetDeltaTime()), m_rect[i], 0, 255, 0);
				glm::vec2 direction = glm::normalize(playerPos - npcPos);
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
		if (m_warriorPos.x != 0 || m_warriorPos.y != 0)
			speed = "Player Speed: " + to_string(abs((static_cast<int>(m_warriorPos.x + m_warriorPos.y))));
		else
			speed = "Player Speed: ";

		font->Write(_renderer->GetRenderer(), speed.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 0, 20 });


		std::string enemySpeed;
		if (m_warriorPos.x != 0 || m_warriorPos.y != 0)
			enemySpeed = "Enemy Speed: " + to_string(abs((static_cast<int>(m_npcPos.x + m_npcPos.y))));
		else
			enemySpeed = "Enemy Speed: ";

		font->Write(_renderer->GetRenderer(), enemySpeed.c_str(), SDL_Color{ 0, 255, 0 }, SDL_Point{ 0, 40 });


		std::string enemyTag = "Enemies tagged: ";
		font->Write(_renderer->GetRenderer(), enemyTag.c_str(), SDL_Color{ 0, 255, 0 }, SDL_Point{ 0, 60 });


		SDL_RenderPresent(_renderer->GetRenderer());
		t->CapFPS();
	}
	delete SpriteAnim::Pool;
	delete SpriteSheet::Pool;
	font->Shutdown();


}

