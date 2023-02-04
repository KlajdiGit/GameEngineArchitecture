#ifndef LEVEL_H
#define LEVEL_H

#include "Unit.h"

class Level : public Resource
{
public:
	//Constructor/Destructor
	Level();
	virtual ~Level();

	//Methods
	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues() override;

private:
	//Members
	int m_mapSizeX;
	int m_mapSizeY;
	float m_gameTime;
	Unit* m_unit;
};

#endif //LEVEL_H

