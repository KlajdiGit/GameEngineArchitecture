#include "PlayerState.h"
#include "InputController.h"
#include "Keyboard.h"
#include "Player.h"
#include "SpriteSheet.h"


/*State 1: Idle – clip 0
• State 2: Roll – clips 0 to 3
• State 3: Paper – clips 4 to 7
• State 4: Scissors – clips 8 – 11
• State 5: Rock – clips 12 - 15*/

IdleState PlayerState::m_idleState;
RollState RollState::m_rollState;
RockState PlayerState::m_rockState;
PaperState PlayerState::m_paperState;
ScissorState PlayerState::m_scissorState;

void IdleState::HandleInput(Player* _player, SDL_Event _event)
{
	if (InputController::Instance().KB()->KeyUp(_event, SDLK_SPACE))
	{
		_player->GetAnimations()->ResetCurrentClip(EN_AN_IDLE);
		_player->SetState(PlayerState::GetIdleState());
	}
}

void IdleState::Update(Player* _player, float _deltaTime)
{
	_player->GetAnimations()->Update(EN_AN_IDLE, _deltaTime, _player->GetSrcRect());
}

void RollState::HandleInput(Player* _player, SDL_Event _event)
{
	if (InputController::Instance().KB()->KeyUp(_event, SDLK_SPACE))
	{
		_player->GetAnimations()->ResetCurrentClip(EN_AN_ROLL);
		_player->SetState(PlayerState::GetIdleState());
	}
}

void RollState::Update(Player* _player, float _deltaTime)
{
	_player->GetAnimations()->Update(EN_AN_ROLL, _deltaTime, _player->GetSrcRect());
}


void RockState::HandleInput(Player* _player, SDL_Event _event)
{
	if (InputController::Instance().KB()->KeyUp(_event, SDLK_SPACE))
	{
		_player->GetAnimations()->ResetCurrentClip(EN_AN_ROCK);
		_player->SetState(PlayerState::GetIdleState());
	}
}

void RockState::Update(Player* _player, float _deltaTime)
{
	_player->GetAnimations()->Update(EN_AN_ROCK, _deltaTime, _player->GetSrcRect());
}

void PaperState::HandleInput(Player* _player, SDL_Event _event)
{
	if (InputController::Instance().KB()->KeyUp(_event, SDLK_SPACE))
	{
		_player->GetAnimations()->ResetCurrentClip(EN_AN_PAPER);
		_player->SetState(PlayerState::GetRollState());
	}
}

void PaperState::Update(Player* _player, float _deltaTime)
{
	_player->GetAnimations()->Update(EN_AN_PAPER, _deltaTime, _player->GetSrcRect());
}

void ScissorState::HandleInput(Player* _player, SDL_Event _event)
{
	if (InputController::Instance().KB()->KeyUp(_event, SDLK_SPACE))
	{
		_player->GetAnimations()->ResetCurrentClip(EN_AN_SCISSOR);
		_player->SetState(PlayerState::GetRollState());
	}
}

void ScissorState::Update(Player* _player, float _deltaTime)
{
	_player->GetAnimations()->Update(EN_AN_SCISSOR, _deltaTime, _player->GetSrcRect());
}