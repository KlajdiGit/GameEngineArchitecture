#ifndef LEVEL_H
#define LEVEL_H

#include "Unit.h"
class InputController;

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
	void RunLevel();
	void HandleInput(SDL_Event _event);
private:
	//Members
	int m_mapSizeX;
	int m_mapSizeY;
	float m_gameTime;
	vector<Unit*> m_units;
	SDL_Event m_sdlEvent;
	bool m_quit;
	InputController* m_input;

};

#endif //LEVEL_H

