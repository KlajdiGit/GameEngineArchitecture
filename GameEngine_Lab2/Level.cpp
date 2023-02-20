#include "Level.h"
#include "Renderer.h"
#include "SpriteSheet.h"
#include "SpriteAnim.h"
#include "TTFont.h"
#include "Timing.h"

Level::Level()
{
	AssetController::Instance().Initialize(10000000); //Allocate 10 MB
	Unit::Pool = new ObjectPool<Unit>();
	SoundEffects::Pool = new ObjectPool<SoundEffects>();

	m_mapSizeX = 0;
	m_mapSizeY = 0;
	m_gameTime = 0.0f;
	m_units.clear();
	m_sdlEvent = { };
}

Level::~Level()
{
	m_units.clear();
	delete SoundEffects::Pool;
	delete Unit::Pool;
	AssetController::Instance().Clear(); //Free 10MB
}


void Level::RunLevel()
{
	AssetController::Instance().Initialize(10000000); //Allocate 10MB
	Renderer* r = &Renderer::Instance();
	Timing* t = &Timing::Instance();
	r->Initialize(1200, 1000);  // 1920x1080

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
			unsigned int xPos = 80* ((SDL_GetTicks() - yPos) / 1000.0f);
			//unsigned int  xPos = count * 10;
			r->RenderTexture(sheet, sheet->Update(EN_AN_RUN, t->GetDeltaTime()), Rect(xPos, yPos, 69 * 1.8 +xPos,yPos + 44 * 1.8));

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

