#include "Level.h"
#include "Renderer.h"
#include "TTFont.h"
#include "SpriteSheet.h"
#include "SpriteAnim.h"
#include "Timing.h"
#include "RenderTarget.h"

Level::Level()
{
	AssetController::Instance().Initialize(10000000); //Allocate 10 MB
	Unit::Pool = new ObjectPool<Unit>();
	SoundEffects::Pool = new ObjectPool<SoundEffects>();

	m_mapSizeX = 0;
	m_mapSizeY = 0;
	m_gameTime = 0.0f;
	m_units.clear();
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

void Level::RunLevel(Renderer* _renderer, Point _p)
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

	SpriteSheet* sheet2 = SpriteSheet::Pool->GetResource();
	sheet2->Load("../Assets/Textures/Warrior.tga");
	sheet2->SetSize(17, 6, 69, 44);
	sheet2->AddAnimation(EN_AN_RUN, 6, 8, 2.0f);


	RenderTarget* rt = new RenderTarget();
	rt->Create(NATIVE_XRES, NATIVE_YRES); //Set to game's native resolution

	//while (m_sdlEvent.type != SDL_QUIT)
	//{
		//SDL_PollEvent(&m_sdlEvent);
		//HandleInput(m_sdlEvent);
	t->Tick();
	//rt->Start();
   // _renderer->SetDrawColor(Color(255, 255, 255, 255));
	//_renderer->ClearScreen();


		//r->RenderTexture(sheet, sheet->Update(EN_AN_IDLE, t->GetDeltaTime()), Rect(ws.X / 2, ws.Y / 2, 69 , (ws.Y / 2) + 44 ));
	    if ( ws.X / 2 == 1920/2 && ws.Y == 1080 /2)
		 _renderer->RenderTexture(sheet, sheet->Update(EN_AN_IDLE, t->GetDeltaTime()), Rect(ws.X / 2, ws.Y / 2, ws.X / 2 + 69, ws.Y / 2 + 44));
		else
		 _renderer->RenderTexture(sheet2, sheet2->Update(EN_AN_RUN, t->GetDeltaTime()), Rect(ws.X / 2, ws.Y / 2, ws.X / 2 + 69, ws.Y / 2 + 44));


		std::string guide = "[D]ecrease speed [I]ncrease speed [S]ave [L]oad [ESC] Quit ";

		font->Write(_renderer->GetRenderer(), guide.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 0, 0 });

		std::string speed = "Player Speed: ";
		font->Write(_renderer->GetRenderer(), speed.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 0, 20 });

		std::string enemySpeed = "Enemy Speed: ";
		font->Write(_renderer->GetRenderer(), enemySpeed.c_str(), SDL_Color{ 0, 255, 0 }, SDL_Point{ 0, 40 });

		std::string enemyTag = "Enemies tagged: ";
		font->Write(_renderer->GetRenderer(), enemyTag.c_str(), SDL_Color{ 0, 255, 0 }, SDL_Point{ 0, 60 });

		
		ws.X += _p.X;
		ws.Y += _p.Y;
	}

