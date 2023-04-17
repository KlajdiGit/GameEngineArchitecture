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
#include "Controller.h"


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
	m_player1Name = "";
	m_player2Name = "";
	m_song = nullptr;
	m_fArial20 = nullptr;
	m_physics = nullptr;
	m_player1 = new Player();
	m_player2 = new Player();
	m_timing = &Timing::Instance();
	m_playerWin = 0;
	m_player1Win = 0;
	m_playerLoss = 0;
	m_player1Loss = 0;
	m_p1Pos = { 20, 30 };
	m_p2Pos = { 20, 330 };
	m_mPos = { };


}

Level::~Level()
{
	m_units.clear();
	delete SoundEffects::Pool;
	delete Unit::Pool;
	AssetController::Instance().Clear(); //Free 10MB
	//m_fArial20->Shutdown();
	if (m_player1 != nullptr)
	{
		delete m_player1;
		m_player1 = nullptr;
	}

	if (m_player2 != nullptr)
	{
		delete m_player2;
		m_player2 = nullptr;
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
			if (m_player1Name.length() == 0 || m_player1Name.length() > 20)
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
			if (m_player2Name.length() == 0 || m_player2Name.length() > 20)
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

	else if (m_input->MS()->Moved(_event, m_mPos) && m_input->MS()->GetButLDown())
	{
		if (m_mPos.X >= 1920 - 280 && m_mPos.Y >= 1080 - 170)
		{
			m_p1Pos.x = 1920 - 320;
			m_p1Pos.y = 1080 - 210;
		}
		else if (m_mPos.X >= 1920 -280 )
		{
			m_p1Pos.x = 1920 - 320;
		}
		else if (m_mPos.Y >= 1080 - 170)
		{
			m_p1Pos.y = 1080 - 210;
		}
		else if (m_mPos.X <= 140)
		{
			m_p1Pos.x = 20;
		}
		else if (m_mPos.Y <=85)
		{
			m_p1Pos.y = 30;
		}
		else if (m_mPos.X <= 0 && m_mPos.Y <= 0)
		{
			m_p1Pos.x = 20;
			m_p1Pos.y = 30;
		}
		else
		{
			m_p1Pos.x = m_mPos.X - 140;
			m_p1Pos.y = m_mPos.Y - 85;
		}
		
	}

	else if (m_input->MS()->Moved(_event, m_mPos) && m_input->MS()->GetButRDown())
	{
		if (m_mPos.X >= 1920 - 280 && m_mPos.Y >= 1080 - 170)
		{
			m_p2Pos.x = 1920 - 320;
			m_p2Pos.y = 1080 - 210;
		}
		else if (m_mPos.X >= 1920 - 280)
		{
			m_p2Pos.x = 1920 - 320;
		}
		else if (m_mPos.Y >= 1080 - 170)
		{
			m_p2Pos.y = 1080 - 210;
		}
		else if (m_mPos.X <= 140)
		{
			m_p2Pos.x = 20;
		}
		else if (m_mPos.Y <= 85)
		{
			m_p2Pos.y = 30;
		}
		else if (m_mPos.X <= 0 && m_mPos.Y <= 0)
		{
			m_p2Pos.x = 20;
			m_p2Pos.y = 30;
		}
		else
		{
			m_p2Pos.x = m_mPos.X - 140;
			m_p2Pos.y = m_mPos.Y - 85;
		}
	}

	else if (m_input->KB()->KeyDown(_event, SDLK_d))
	{
	    if(m_p1Pos.x <= 1920 - 280)
		m_p1Pos.x +=  400 * m_timing->GetDeltaTime();
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_a))
	{
		if (m_p1Pos.x >= 20)
		m_p1Pos.x -= 400 * m_timing->GetDeltaTime();
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_w))
	{
		if (m_p1Pos.y >= 30)
		m_p1Pos.y -= 400 * m_timing->GetDeltaTime();
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_s))
	{
		if (m_p1Pos.y <= 1080 - 170)
		m_p1Pos.y += 400 * m_timing->GetDeltaTime();
	}

	else if (m_input->KB()->KeyDown(_event, SDLK_RIGHT))
	{
		if (m_p2Pos.x <= 1920 - 280)
			m_p2Pos.x += 400 * m_timing->GetDeltaTime();
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_LEFT))
	{
		if (m_p2Pos.x >= 20)
			m_p2Pos.x -= 400 * m_timing->GetDeltaTime();
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_UP))
	{
		if (m_p2Pos.y >= 30)
			m_p2Pos.y -= 400 * m_timing->GetDeltaTime();
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_DOWN))
	{
		if (m_p2Pos.y <= 1080 - 170)
			m_p2Pos.y += 400 * m_timing->GetDeltaTime();
	}

	else if ((m_input->CT()->Added(_event)) ||
		      (m_input->CT()->Removed(_event)) ||
			  (m_input->CT()->ProcessButtons(_event)) ||
			  (m_input->CT()->ProcessMotion(_event)))
			  {
				  
				  /*NOTE: The logic implemented to handle when we pass the boundaries
				          will make both animations to be in the same coordinates*/


			      if (_event.caxis.axis == 0)
				  {
					  if (_event.caxis.value >= 1920 - 280)
						  m_p1Pos.x = 1920 - 320;

					  else if (_event.caxis.value <= 140)
					  {
						  m_p1Pos.x = 20;
					  }
					  else
						  m_p1Pos.x = _event.caxis.value;

				  }
				  else if (_event.caxis.axis == 1)
				  {
					  if (_event.caxis.value >= 1080 - 170)
					  {
						  m_p1Pos.y = 1080 - 210;
					  }
					  else if (_event.caxis.value <= 85)
					  {
						  m_p1Pos.y = 30;
					  }
					  else
					  m_p1Pos.y = _event.caxis.value;
				  }

				 
				  if (_event.caxis.axis == 2) 
				  {
					  if (_event.caxis.value >= 1920 - 280)
						  m_p2Pos.x = 1920 - 320;

					  else if (_event.caxis.value <= 140)
					  {
						  m_p2Pos.x = 20;
					  }

					  else
						  m_p1Pos.x = _event.caxis.value;
				  }
				  else if (_event.caxis.axis == 3) 
				  {
					  if (_event.caxis.value >= 1080 - 170)
					  {
						  m_p2Pos.y = 1080 - 210;
					  }
					  else if (_event.caxis.value <= 85)
					  {
						  m_p2Pos.y = 30; 
					  }
					  else
						  m_p2Pos.y = _event.caxis.value;
				  }


			  }
		
	else
	{
		m_player1->HandleInput(_event, m_timing->GetDeltaTime());
		m_player2->HandleInput(_event, m_timing->GetDeltaTime());
	}
	m_input->MS()->ProcessButtons(_event);
}





void Level::RunLevel(Renderer* _renderer)
{
	//Timing* t = &Timing::Instance();
	_renderer->EnumerateDisplayModes();
	_renderer->ChangeDisplayMode(&_renderer->GetResolutions()[0]);

	TTFont* t = new TTFont();
	t->Initialize(20);


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
		t->Write(_renderer->GetRenderer(), guideline.c_str(), SDL_Color{ 255, 255, 255 }, SDL_Point{ 10, 1050 });


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
	m_effects[0] = m_audio->LoadEffect("../Assets/Audio/Effects/Whoosh.wav");
	m_effects[1] = m_audio->LoadEffect("../Assets/Audio/Effects/DistantGunshot.mp3");

	std::string resultP1 = "Waiting to start...";
	
	std::string resultP2 = "Waiting to start...";
	


	while (!m_quit)
	{
		m_timing->Tick();
		_renderer->SetDrawColor(Color(255, 255, 255, 255));
		_renderer->ClearScreen();
		/*resultP1 = "Waiting to start...";
		resultP2 = "Waiting to start...";*/

 		while (SDL_PollEvent(&m_sdlEvent) != 0)
		{
			


  			if (m_sdlEvent.type == SDL_KEYUP && m_sdlEvent.key.keysym.sym == SDLK_SPACE)
			{
				/*resultP1 = "Rolling...";
				resultP2 = "Rolling...";*/

				//m_audio->Play(m_effects[0]);
				int win = 0, win1 = 0, loss = 0, loss1 = 0;

				if (m_player1->GetState() == PlayerState::GetRollState() && m_player2->GetState() == PlayerState::GetRollState())
				{
					m_audio->Play(m_effects[0]);

					//m_audio->Play(m_effects[1]);
					resultP1 = "Rolling...";
					resultP2 = "Rolling...";
				}

				else if (m_player1->GetState() == m_player2->GetState() &&
					     m_player1->GetState() != PlayerState::GetRollState() && m_player2->GetState() != PlayerState::GetRollState())
				{
					//m_audio->Play(m_effects[1]);
					resultP1 = "DRAW!";
					resultP2 = "DRAW!";

				}
				else
				{
					//m_audio->Play(m_effects[1]);

					if (m_player1->GetState() == PlayerState::GetRockState() && m_player2->GetState() == PlayerState::GetScissorState() ||
						m_player1->GetState() == PlayerState::GetPaperState() && m_player2->GetState() == PlayerState::GetRockState() ||
						m_player1->GetState() == PlayerState::GetScissorState() && m_player2->GetState() == PlayerState::GetPaperState() ||
						m_player2->GetState() == PlayerState::GetRockState() && m_player1->GetState() == PlayerState::GetPaperState() ||
						m_player2->GetState() == PlayerState::GetPaperState() && m_player1->GetState() == PlayerState::GetScissorState() ||
						m_player2->GetState() == PlayerState::GetScissorState() && m_player1->GetState() == PlayerState::GetRockState())
					{
						std::cout << "Player 1 wins!" << std::endl;
						resultP1 = "WINNER!";
						resultP2 = "LOSSER!";
						m_playerWin++;
						m_player1Loss++;
					}
					else
					{
						std::cout << "Player 2 wins!" << std::endl;
						resultP2 = "WINNER!";
						resultP1 = "LOSSER!";
						m_player1Win++;
						m_playerLoss++;

					}
				}
				/*m_player1Win += loss1;
				m_player1Win += win1;
				m_playerLoss += loss;
				m_playerWin += win; */

			}
			HandleInputLvTwo(m_sdlEvent);
		}


		m_player1->Update(m_timing->GetDeltaTime());
		m_player1->Render(_renderer, m_p1Pos);

		m_player2->Update(m_timing->GetDeltaTime());
		m_player2->Render(_renderer, m_p2Pos);


		

		std::string numWins = "Wins: " + to_string(m_playerWin);
 		std::string numLosses = "Losses: " + to_string(m_playerLoss);

		std::string numWins1 = "Wins: " + to_string(m_player1Win);
		std::string numLosses1 = "Losses: " + to_string(m_player1Loss); 
		
		
		

		m_fArial20->Write(_renderer->GetRenderer(), m_player1Name.c_str(), SDL_Color{ 0, 255, 0 }, SDL_Point{ (int)m_p1Pos.x,  (int)m_p1Pos.y - 20});
		m_fArial20->Write(_renderer->GetRenderer(), resultP1.c_str(), SDL_Color{ 255, 0, 0 }, SDL_Point{ (int)m_p1Pos.x,  (int)m_p1Pos.y});
		m_fArial20->Write(_renderer->GetRenderer(), numWins.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ (int)m_p1Pos.x,  (int)m_p1Pos.y + 20 });
		m_fArial20->Write(_renderer->GetRenderer(), numLosses.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ (int)m_p1Pos.x,  (int)m_p1Pos.y + 40 });



		m_fArial20->Write(_renderer->GetRenderer(), m_player2Name.c_str(), SDL_Color{ 0, 255, 0 }, SDL_Point{ (int)m_p2Pos.x,  (int)m_p2Pos.y - 20 });
		m_fArial20->Write(_renderer->GetRenderer(), resultP2.c_str(), SDL_Color{ 255, 0, 0 }, SDL_Point{ (int)m_p2Pos.x,  (int)m_p2Pos.y});
		m_fArial20->Write(_renderer->GetRenderer(), numWins1.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ (int)m_p2Pos.x,  (int)m_p2Pos.y + 20 });
		m_fArial20->Write(_renderer->GetRenderer(), numLosses1.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ (int)m_p2Pos.x,  (int)m_p2Pos.y + 40 });

		std::string guideLine;
		std::string guideLine2;

		guideLine = "Frames Per Second: " + to_string(m_timing->GetFPS()) + "   Game Time: " + to_string(SDL_GetTicks() / 1000) + "   Saves: " + "   Loads: ";
		guideLine2 = "Quit [ESC]   Next Game State [Space]   Save [F5]   Load[F7]" ;
		m_fArial20->Write(_renderer->GetRenderer(), guideLine.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{10, 1030});
		m_fArial20->Write(_renderer->GetRenderer(), guideLine2.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 10, 1060 });


		SDL_RenderPresent(_renderer->GetRenderer());
		m_timing->CapFPS();
	}
}