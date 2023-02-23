#ifndef LEVEL_H
#define LEVEL_H

#include "Unit.h"
#include "Renderer.h"

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
	void RunLevel2(unsigned int _saveTime);


private:
	//Members
	int m_mapSizeX;
	int m_mapSizeY;
	float m_gameTime;
	vector<Unit*> m_units;
	
};

#endif //LEVEL_H

