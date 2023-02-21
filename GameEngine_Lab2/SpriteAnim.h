#ifndef SPRITEANIM_H
#define SPRITEANIM_H

#include "Resource.h"

class SpriteAnim : Resource
{
public:
	//Constructors/Destructors
	SpriteAnim();
	virtual ~SpriteAnim();

	//Accessors
	short GetClipCurrent() { return (short)m_clipCurrent; }

	//Methods
	virtual void Serialize(std::ostream& _stream);
	virtual void Deserialize(std::istream& _stream);
	virtual void ToString();

	void ClearMemory();
	void Create(short _clipStart, short _clipCount, float _clipSpeed);
	void Update(float _deltaTime);

	//Memeber
	static ObjectPool<SpriteAnim>* Pool;

private:
	//Members
	short m_clipStart = 0;
	short m_clipCount = 0;
	short m_clipEnd =0 ;
	float m_clipCurrent = 0.0f;
	float m_clipSpeed = 0.0f;
};

#endif SPRITEANIM_H
