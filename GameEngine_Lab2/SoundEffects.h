#ifndef SOUND_EFFECT_H
#define SOUND_EFFECT_H

#include "Resource.h"
#include "Asset.h"

class SoundEffects:public Resource
{
public:
	//Constructor/Destructor
	SoundEffects();
	virtual ~SoundEffects();

	//Methods
	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues() override;

	//Members
	static ObjectPool<SoundEffects>* Pool;

private:
	Asset* m_effect;
};

#endif //SOUND_EFFECT_H


