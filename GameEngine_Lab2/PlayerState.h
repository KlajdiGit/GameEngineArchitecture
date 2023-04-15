#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include "StandardIncludes.h"


/*State 1: Idle – clip 0
• State 2: Roll – clips 0 to 3
• State 3: Paper – clips 4 to 7
• State 4: Scissors – clips 8 – 11
• State 5: Rock – clips 12 - 15*/


class Player;
class IdleState;
class RollState;
class RockState;
class PaperState;
class ScissorState;

class PlayerState
{
public:
	PlayerState() { }
	virtual ~PlayerState() { }

	static IdleState* GetIdleState() { return &m_idleState; }
	static RollState* GetRollState() { return &m_rollState; }
	static RockState* GetRockState() { return &m_rockState; }
	static PaperState* GetPaperState() { return &m_paperState; }
	static ScissorState* GetScissorState() { return &m_scissorState; }

	virtual void HandleInput(Player* _player, SDL_Event _event) = 0;
	virtual void Update(Player* _player, float _deltaTime) = 0;

private:
	static IdleState m_idleState;
	static RollState m_rollState;
	static RockState m_rockState;
	static PaperState m_paperState;
	static ScissorState m_scissorState;
};

class IdleState : public PlayerState
{
public:
	IdleState() { }
	virtual ~IdleState() { }

	virtual void HandleInput(Player* _player, SDL_Event _event) override;
	virtual void Update(Player* _player, float _deltaTime) override;
};

class RollState : public PlayerState
{
public:
	RollState() { }
	virtual ~RollState() { }

	virtual void HandleInput(Player* _player, SDL_Event _event) override;
	virtual void Update(Player* _player, float _deltaTime) override;
};

class RockState : public PlayerState
{
public:
	RockState() { }
	virtual ~RockState() { }

	virtual void HandleInput(Player* _player, SDL_Event _event) override;
	virtual void Update(Player* _player, float _deltaTime) override;
};

class PaperState : public PlayerState
{
public:
	PaperState() { }
	virtual ~PaperState() { }

	virtual void HandleInput(Player* _player, SDL_Event _event) override;
	virtual void Update(Player* _player, float _deltaTime) override;
};

class ScissorState : public PlayerState
{
public:
	ScissorState() { }
	virtual ~ScissorState() { }

	virtual void HandleInput(Player* _player, SDL_Event _event) override;
	virtual void Update(Player* _player, float _deltaTime) override;
};

#endif //PLAYER_STATE_H