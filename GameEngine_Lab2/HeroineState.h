#ifndef HEROINE_STATE_H
#define HEROINE_STATE_H

#include "StandardIncludes.h"

class Heroine;
class StandingState;
class DuckingState;
class JumpingState;
class DivingState;

class HeroineState
{
public:
	//Constructors / Destructors
	HeroineState() { }
	virtual ~HeroineState() { }

	//Accessors
	static StandingState* GetStandingState() { return &m_standing; }
	static DuckingState* GetDuckingState() { return &m_ducking; }
	static JumpingState* GetJumpingState() { return &m_jumping; }
	static DivingState* GetDivingState() { return &m_diving; }


	//Methods
	virtual void HandleInput(Heroine* _heroine, SDL_Event _event) = 0;
	virtual void Update(Heroine* _heroine, float _deltaTime) = 0;

private:
	//Members
	static StandingState m_standing;
	static DuckingState m_ducking;
	static JumpingState m_jumping;
	static DivingState m_diving;

};


class StandingState : public HeroineState
{
public:
	// Constructors / Destructors
	StandingState() { }
	virtual ~StandingState() { }

	//Methods
	void HandleInput(Heroine* _heroine, SDL_Event _event) override;
	void Update(Heroine* _heroine, float _deltaTime) override;
};

class DuckingState : public HeroineState
{
public:
	// Constructors / Destructors
	DuckingState() { }
	virtual ~DuckingState() { }

	//Methods
	void HandleInput(Heroine* _heroine, SDL_Event _event) override;
	void Update(Heroine* _heroine, float _deltaTime) override;
};


class JumpingState : public HeroineState
{
public:
	// Constructors / Destructors
	JumpingState() { }
	virtual ~JumpingState() { }

	//Methods
	void HandleInput(Heroine* _heroine, SDL_Event _event) override;
	void Update(Heroine* _heroine, float _deltaTime) override;
};


class DivingState : public HeroineState
{
public:
	// Constructors / Destructors
	DivingState() { }
	virtual ~DivingState() { }

	//Methods
	void HandleInput(Heroine* _heroine, SDL_Event _event) override;
	void Update(Heroine* _heroine, float _deltaTime) override;
};

#endif //HEROINE_STATE_H