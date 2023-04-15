#ifndef LEVEL_H
#define LEVEL_H

#include "Unit.h"
class Renderer;
class InputController;
class AudioController;
class TTFont;
class Song;
class PhysicsController;
class Player;
class Timing;


class Level : public Resource
{
public:
	//Constructor/Destructor
	Level();
	~Level();

	//Methods
	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues() override;
	void RunLevel(Renderer* _renderer);
	void HandleInput(SDL_Event _event);
	void RunLevel2(Renderer* _renderer);
	void HandleInputLv2(SDL_Event _event);
	//void RunLevel1(Renderer* _renderer, glm::vec2 m_kPos, glm::vec2 m_npcPos);


private:
	//Members
	int m_mapSizeX;
	int m_mapSizeY;
	float m_gameTime;
	vector<Unit*> m_units;
	Point m_point;
	SDL_Event m_sdlEvent;
	InputController* m_input;
	bool m_quit;
	bool m_level2;
	AudioController* m_audio;
	Song* m_song;
	SoundEffects* m_effect;
	string m_player1Name;
	string m_player2Name;
	TTFont* m_fArial20;
	Player* m_player;
	Timing* m_timing;
	PhysicsController* m_physics;

};

#endif //LEVEL_H


