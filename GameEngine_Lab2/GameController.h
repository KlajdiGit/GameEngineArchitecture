#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"

class Renderer;
class TTFont;
class InputController;
class AudioController;
class SoundEffects;
class Song;

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
	//string m_text;
	//string m_smPos;
	//Point m_mPos;
	//string m_ctInfo = "";

};

#endif //GAME_CONTROLLER_H