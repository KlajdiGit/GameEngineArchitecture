#ifndef LEVEL_H
#define LEVEL_H

#include "Unit.h"

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
private:
	//Members
	int m_mapSizeX;
	int m_mapSizeY;
	float m_gameTime;
	vector<Unit*> m_units;
	SDL_Event m_sdlEvent;

};

#endif //LEVEL_H

