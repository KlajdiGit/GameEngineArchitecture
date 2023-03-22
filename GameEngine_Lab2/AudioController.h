#ifndef AUDIOCONTROLLER_H
#define AUDIOCONTROLLER_H

#include "StandardIncludes.h"

constexpr int MaxEffectChannels = 16;

class SoundEffects;
class Song;

class AudioController : public Singleton<AudioController>
{
public:
	//Constructor/Destructor
	AudioController();
	virtual ~AudioController();

	//Accessors
	string* GetCurrentEffects() { return m_currentEffects; }
	string GetCurrentEffect() { return m_currentEffect; }
	string GetMusicTitle() { return m_musicTitle; }
	string GetMusicLength() { return m_musicLength; }

	//Methods
	SoundEffects* LoadEffect(string _guid);
	Song* LoadSong(string _guid);
	void Play(SoundEffects* _effect);
	void Play(Song* _effect);
	void StopMusic();
	void PauseMusic();
	void ResumeMusic();
	double MusicPosition();
	void Shutdown();

	static void CatchChannelDone(int _channel);

private:
	//Methods
	Mix_Chunk* GetSDLSFX(SoundEffects* _effect);
	Mix_Music* GetSDLMusic(Song* _song);

	//Members
	map<string, Mix_Chunk*> m_effects;
	map<string, Mix_Music*> m_songs;
	string m_currentEffect;
	string m_musicLength;
	string m_currentEffects[MaxEffectChannels];
	string m_musicTitle;
	Mix_Music* m_currentSong;
};

#endif //AUDIOCONTROLLER_H


