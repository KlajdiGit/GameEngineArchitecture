#include "PlayerState.h"
#include "InputController.h"
#include "Keyboard.h"
#include "Player.h"
#include "SpriteSheet.h"

IdleState PlayerState::m_idleState;
RollState PlayerState::m_rollState;
RockState PlayerState::m_rockState;
PaperState PlayerState::m_paperState;
ScissorState PlayerState::m_scissorState;

void IdleState::HandleInput(Player* _player, SDL_Event _event)
{
	if (InputController::Instance().KB()->KeyUp(_event, SDLK_SPACE))
	{
		_player->SetState(PlayerState::GetRollState());
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
		int stateIndex = rand() % 3;
		switch (stateIndex)
		{
		case 0:
			_player->SetState(PlayerState::GetRockState());
			break;
		case 1:
			_player->SetState(PlayerState::GetPaperState());
			break;
		case 2:
			_player->SetState(PlayerState::GetScissorState());
			break;
		default:
			break;
		}
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
		_player->SetState(PlayerState::GetIdleState());
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
		_player->SetState(PlayerState::GetIdleState());
	}
}

void ScissorState::Update(Player* _player, float _deltaTime)
{
	_player->GetAnimations()->Update(EN_AN_SCISSOR, _deltaTime, _player->GetSrcRect());
	
}
