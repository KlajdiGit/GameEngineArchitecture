#ifndef LEVEL_H
#define LEVEL_H

#include "Unit.h"
class Renderer;
class InputController;
class AudioController;


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
	//void RunLevel1(Renderer* _renderer, glm::vec2 m_kPos, glm::vec2 m_npcPos);


private:
	//Members
	int m_mapSizeX;
	int m_mapSizeY;
	float m_gameTime;
	vector<Unit*> m_units;
	Point m_point;
	glm::vec2 m_warriorPos;
	glm::vec2 m_npcPos;
	SDL_Event m_sdlEvent;
	InputController* m_input;
	bool m_quit;
	AudioController* m_audio;
	SoundEffects* m_effect;
	Rect m_rect[10];
	int m_enemyTagged;
	//vector <Rect> m_rect;
};

#endif //LEVEL_H

