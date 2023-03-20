#include "AudioController.h"
#include "SoundEffects.h"
#include "Song.h"

AudioController::AudioController()
{
	M_ASSERT((Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) >= 0), "Failed to initialize Mix Audio");
	SoundEffects::Pool = new ObjectPool<SoundEffects>();
	m_currentSong = nullptr;
}

AudioController::~AudioController()
{
	Shutdown();
}

SoundEffects* AudioController::LoadEffect(string _guid)
{
	SoundEffects* effect = SoundEffects::Pool->GetResource();
	effect->Load(_guid);
	return effect;
}