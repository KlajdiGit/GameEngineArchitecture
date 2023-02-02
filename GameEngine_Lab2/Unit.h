#ifndef UNIT_H
#define UNIT_H

#include "Resource.h"
#include "SoundEffects.h"

class Unit:public Resource
{
public:
	//Coonstructor/Destructor
	Unit();
	virtual ~Unit();

	//Method
	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues() override;

	//Members
	static ObjectPool<Unit>* Pool;
private:
	//Members
	SoundEffects* m_soundEffect;
};

#endif //UNIT_H

