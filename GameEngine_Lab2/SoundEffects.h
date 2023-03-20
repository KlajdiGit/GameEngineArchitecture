#ifndef SOUND_EFFECT_H
#define SOUND_EFFECT_H

#include "Resource.h"
class Asset;

class SoundEffects:public Resource
{
public:
	//Constructor/Destructor
	SoundEffects();
	virtual ~SoundEffects();

	//Accessors
	Asset* GetData() { return m_effect; }


	//Methods
	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void Load(string _guid);

	//Members
	static ObjectPool<SoundEffects>* Pool;

private:
	Asset* m_effect;
};

#endif //SOUND_EFFECT_H


