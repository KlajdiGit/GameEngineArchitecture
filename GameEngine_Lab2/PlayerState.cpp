/*
#include "PlayerState.h"
#include "InputController.h"
#include "Keyboard.h"
#include "Player.h"
#include "SpriteSheet.h"
*/

/*
IdleState PlayerState::m_idleState;
RollState PlayerState::m_rollState;
RockState PlayerState::m_rockState;
PaperState PlayerState::m_paperState;
ScissorState PlayerState::m_scissorState;

void IdleState::HandleInput(Player* _player, SDL_Event _event)
{
	if (InputController::Instance().KB()->KeyUp(_event, SDLK_SPACE))
	{
		//_player->GetAnimations()->ResetCurrentClip(EN_AN_IDLE);
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
		//_player->GetAnimations()->ResetCurrentClip(EN_AN_ROLL);
		_player->SetState(PlayerState::GetScissorState());
	}
}

void RollState::Update(Player* _player, float _deltaTime)
{
	_player->GetAnimations()->Update(EN_AN_ROLL, _deltaTime, _player->GetSrcRect());
	if (_player->GetAnimations()->GetCurrentClip(EN_AN_ROLL) >= 3.0f)
	{
		_player->GetAnimations()->ResetCurrentClip(EN_AN_ROLL);
		_player->SetState(PlayerState::GetScissorState());
	}
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

	if (_player->GetAnimations()->GetCurrentClip(EN_AN_ROCK) >= 15.0f)
	{
		_player->GetAnimations()->ResetCurrentClip(EN_AN_ROCK);
		_player->SetState(PlayerState::GetIdleState());
	}
}

void PaperState::HandleInput(Player* _player, SDL_Event _event)
{
	if (InputController::Instance().KB()->KeyUp(_event, SDLK_SPACE))
	{
		_player->GetAnimations()->ResetCurrentClip(EN_AN_PAPER);
		_player->SetState(PlayerState::GetIdleState());
	}
}

void PaperState::Update(Player* _player, float _deltaTime)
{
	_player->GetAnimations()->Update(EN_AN_PAPER, _deltaTime, _player->GetSrcRect());
	if (_player->GetAnimations()->GetCurrentClip(EN_AN_PAPER) >= 6.0f)
	{
		_player->GetAnimations()->ResetCurrentClip(EN_AN_PAPER);
		_player->SetState(PlayerState::GetIdleState());
	}
}

void ScissorState::HandleInput(Player* _player, SDL_Event _event)
{
	if (InputController::Instance().KB()->KeyUp(_event, SDLK_SPACE))
	{
		_player->GetAnimations()->ResetCurrentClip(EN_AN_SCISSOR);
		_player->SetState(PlayerState::GetIdleState());
	}
}

void ScissorState::Update(Player* _player, float _deltaTime)
{
	_player->GetAnimations()->Update(EN_AN_SCISSOR, _deltaTime, _player->GetSrcRect());
	if (_player->GetAnimations()->GetCurrentClip(EN_AN_SCISSOR) >= 11.0f)
	{
		_player->GetAnimations()->ResetCurrentClip(EN_AN_SCISSOR);
		_player->SetState(PlayerState::GetIdleState());
	}
} */
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
		SDL_Log("Entering Roll state...");
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
		int randomNum = rand() % 3; // Generate a random number from 0 to 2
		switch (randomNum)
		{
		case 0:
			_player->SetState(PlayerState::GetRockState());
			SDL_Log("Entering Rock state...");
			break;
		case 1:
			_player->SetState(PlayerState::GetPaperState());
			SDL_Log("Entering Paper state...");
			break;
		case 2:
			_player->SetState(PlayerState::GetScissorState());
			SDL_Log("Entering Scissor state...");
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
		SDL_Log("Entering Idle state...");
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
		SDL_Log("Entering Idle state...");
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
		SDL_Log("Entering Idle state...");
	}
}

void ScissorState::Update(Player* _player, float _deltaTime)
{
	_player->GetAnimations()->Update(EN_AN_SCISSOR, _deltaTime, _player->GetSrcRect());
	
}
