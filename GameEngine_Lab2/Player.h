#ifndef PLAYER_H
#define PLAYER_H

#include "PlayerState.h"
#include "RigidBody.h"

class SpriteSheet;
class Renderer;


class Player
{
public:
	Player();
	virtual ~Player();

	PlayerState* GetState() { return m_state; }
	void SetState(PlayerState* _state) { m_state = _state; }
	SpriteSheet* GetAnimations() { return m_animations; }
	Rect* GetSrcRect() { return &m_srcRect; }
	RigidBody* GetRigidBody() { return m_rigidBody; }

	virtual void HandleInput(SDL_Event _event, float _deltaTime);
	virtual void Update(float _deltaTime);
	virtual void Render(Renderer* _renderer);

private:
	RigidBody* m_rigidBody;
	PlayerState* m_state;
	SpriteSheet* m_animations;
	Rect m_srcRect;

};

#endif //PLAYER_H