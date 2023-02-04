#include "SoundEffects.h"

ObjectPool<SoundEffects>* SoundEffects::Pool = nullptr;

SoundEffects::SoundEffects()
{
	m_effect = nullptr;
}

SoundEffects::~SoundEffects()
{
}

void SoundEffects::AssignNonDefaultValues()
{
	m_effect = AssetController::Instance().GetAsset("SoundEffect.wav");	
	Resource::AssignNonDefaultValues();
}

void SoundEffects::Serialize(std::ostream& _stream)
{
	SerializeAsset(_stream, m_effect);
	Resource::Serialize(_stream);
}

void SoundEffects::Deserialize(std::istream& _stream)
{
	DeserializeAsset(_stream, m_effect);
	Resource::Deserialize(_stream);
}

void SoundEffects::ToString()
{
	cout << "SOUND EFFECT" << endl;
	m_effect->ToString();
	Resource::ToString();
}