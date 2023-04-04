#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "AudioController.h"

class Renderer;
class TTFont;
class InputController;
class AudioController;
class SoundEffects;
class Song;
class WavDraw;
class Level;

class GameController : public Singleton<GameController>
{
public:
	//Constructors/Destructors
	GameController();
	virtual ~GameController();

	// Methods
	void RunGame();
	void Initialize();
	void HandleInput(SDL_Event _event);
	void ShutDown();

private:
	SDL_Event m_sdlEvent;
	Renderer* m_renderer;
	TTFont* m_fArial20;
	bool m_quit;
	InputController* m_input;
	AudioController* m_audio;
	SoundEffects* m_effect;
	Song* m_song;
	WavDraw* m_wavDraw;
	SoundEffects* m_effects[MaxEffectChannels];
	float m_zoomY;
	Level* m_lv;
	glm::vec2 m_kPos;
	bool m_right;
};

#endif //GAME_CONTROLLER_H