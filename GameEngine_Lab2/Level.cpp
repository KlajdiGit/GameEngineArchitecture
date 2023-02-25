#include "Level.h"
#include "Renderer.h"
#include "SpriteSheet.h"
#include "SpriteAnim.h"
#include "TTFont.h"
#include "Timing.h"
#include <time.h>
#include <cstdlib>

Renderer* r = &Renderer::Instance();



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


void Level::RunLevel()
{
	AssetController::Instance().Initialize(10000000); //Allocate 10MB
	Timing* t = &Timing::Instance();
	r->Initialize(1920, 1080);  
	TTFont* font = new TTFont();
	font->Initialize(20);

	Point ws = r->GetWindowSize();

	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
	SpriteSheet* sheet = SpriteSheet::Pool->GetResource();
	sheet->Load("../Assets/Textures/Warrior.tga");
	sheet->SetSize(17, 6, 69, 44);
	sheet->AddAnimation(EN_AN_RUN, 6, 8, 4.8f);

	unsigned int xPos = 1;
	unsigned int saveTime;

	while (xPos < 1920)
	{
		t->Tick();
		srand(time(0)); // part of my idea to randomize the speed

		r->SetDrawColor(Color(128, 128, 128, 255));
		r->ClearScreen();
		for (unsigned int count = 0; count < 10; count++)
		{

			unsigned int yPos = 10 + count * 100;
			// my idea of making randomized speed. Assuming the normal walk speed is ((((int)SDL_GetTicks()) -xPos) /1000)
			// which is then multiplied by a speed coefficient 
			//xPos = ((rand() % 21) + 80) *((((int)SDL_GetTicks()) -xPos) /1000) ;
			// 80 will just be in this case the miniaml speed coefficient
			xPos = 80 * (SDL_GetTicks() - xPos) / 1000.0f; 

			r->RenderTexture(sheet, sheet->Update(EN_AN_RUN, t->GetDeltaTime()), Rect(xPos, yPos, 69 * 1.8 + xPos, yPos + 44 * 1.8));
		}


	

		std::string s = "Frames Per Second: " + std::to_string(t->GetFPS());
		font->Write(r->GetRenderer(), s.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 0, 0 });

		saveTime = SDL_GetTicks() / 1000;
	
		s = "Game Time: " + std::to_string(saveTime);
		font->Write(r->GetRenderer(), s.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 250, 0 });
		s = "Auto Save: ";
		if (saveTime >= 5 )
		{
			ofstream writeStream("level1.bin", ios::out | ios::binary);
			Level::Serialize(writeStream);
			sheet->Serialize(writeStream);
			writeStream.close();
			//sheet->Load("level1.bin");

			s += " Yes";
		}
		else {
			s += " No";
		}
		font->Write(r->GetRenderer(), s.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 400, 0 });



		SDL_RenderPresent(r->GetRenderer());
	}

	Level::RunLevel2(saveTime);

	delete SpriteAnim::Pool;
	delete SpriteSheet::Pool;

	font->Shutdown();
	r->Shutdown();
}



void Level::RunLevel2(unsigned int _saveTime)
{
	AssetController::Instance().Initialize(10000000); //Allocate 10MB
	Timing* t = &Timing::Instance();

	TTFont* font = new TTFont();
	font->Initialize(20);

	Point ws = r->GetWindowSize();

	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
	SpriteSheet* sheet = SpriteSheet::Pool->GetResource();
	sheet->Load("../Assets/Textures/Warrior.tga");
	sheet->SetSize(17, 6, 69, 44);
	sheet->AddAnimation(EN_AN_RUN, 6, 8, 2.0f);

	SpriteSheet* sheet2 = SpriteSheet::Pool->GetResource();
	sheet2->Load("../Assets/Textures/Rock.tga");
	sheet2->SetSize(1, 4, 20, 44);
	sheet2->AddAnimation(EN_ROCK_FALL, 0, 0, 4.8f);

	SpriteSheet* sheet3 = SpriteSheet::Pool->GetResource();
	sheet3->Load("../Assets/Textures/Warrior.tga");
	sheet3->SetSize(17, 6, 69, 44);
	sheet3->AddAnimation(EN_AN_DEATH, 26, 11, 4.8f);

	unsigned int xPos = 1;
	unsigned int yPos2 = 1;
	unsigned int x = 1;

	while ( xPos < 1920 )
	{

		t->Tick();
		srand(time(0));

		r->SetDrawColor(Color(0, 128, 0, 255));
		r->ClearScreen();
		for (unsigned int count = 0; count < 10; count++)
		{

			unsigned int yPos = 10 + count * 100;
			xPos = (80 * ((SDL_GetTicks() - yPos) / 1000.0f)) - 1920;
			unsigned int xPos2 = 50 + count * 100;
			//xPos = ((rand() % 21) + 80) *((((int)SDL_GetTicks()) -xPos) /1000) ;
			r->RenderTexture(sheet2, sheet2->Update(EN_ROCK_FALL, t->GetDeltaTime()), Rect(xPos2, xPos /** x*/, 20 * 1.0 + xPos2, xPos + 44 * 1.0));
		

			if (-1 * (xPos - yPos) <= 20 || xPos - yPos <= 20)
			{
               // the logic to remove the rocks from my screen was to make the y coordinate big enough
			   // to be not visible on the screen. Not functional.
 			   //x = 300;
               // Didn't achieve to play the full death animation 
			   r->RenderTexture(sheet3, sheet3->Update(EN_AN_DEATH, t->GetDeltaTime()), Rect(xPos, yPos , 69 * 1.8 + xPos, yPos + 44 * 1.8));

			}
			else 
			{
				r->RenderTexture(sheet, sheet->Update(EN_AN_RUN, t->GetDeltaTime()), Rect(xPos, yPos, 69 * 1.8 + xPos, yPos + 44 * 1.8));

			}

		}

	

		std::string s = "Frames Per Second: " + std::to_string(t->GetFPS());
		font->Write(r->GetRenderer(), s.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 0, 0 });

		unsigned int saveTime = SDL_GetTicks() / 1000 - _saveTime;

		s = "Game Time: " + std::to_string(saveTime);
		font->Write(r->GetRenderer(), s.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 250, 0 });
		s = "Auto Save: ";
		if (saveTime >= 5)
		{
			ofstream writeStream("level2.bin", ios::out | ios::binary);
			Level::Serialize(writeStream);
			sheet->Serialize(writeStream);
			sheet2->Serialize(writeStream);
			sheet3->Serialize(writeStream);
			writeStream.close();

			s += " Yes";
		}
		else {
			s += " No";
		}
		font->Write(r->GetRenderer(), s.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 400, 0 });

	
		SDL_RenderPresent(r->GetRenderer());
	}

	

	font->Shutdown();
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

