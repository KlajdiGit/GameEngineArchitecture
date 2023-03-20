#include "SoundEffects.h"

ObjectPool<SoundEffects>* SoundEffects::Pool = nullptr;

SoundEffects::SoundEffects()
{
	m_effect = nullptr;
}

SoundEffects::~SoundEffects()
{
}

void SoundEffects::Load(string _guid)
{
	m_effect = AssetController::Instance().GetAsset(_guid);	
}

void SoundEffects::Serialize(std::ostream& _stream)
{
	SerializeAsset(_stream, m_effect);
}

void SoundEffects::Deserialize(std::istream& _stream)
{
	DeserializeAsset(_stream, m_effect);
}

void SoundEffects::ToString()
{
	cout << "SOUND EFFECT" << endl;
	m_effect->ToString();
	Resource::ToString();
}