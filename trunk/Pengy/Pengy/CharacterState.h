#pragma once
#include "Win.h"
#include "MessageQueue.h"
#include "Character.h"

class CharacterStateMachine;

class CharacterState
{
protected:
	CharacterStateMachine * pStateMachine;

public:
	CharacterState(void);
	CharacterState(CharacterStateMachine * pStateMachine);
	~CharacterState(void);
	virtual void Up() = 0;
	virtual void Down() = 0;
	virtual void Left() = 0;
	virtual void Right() = 0;
	virtual void Spacebar() = 0;
	virtual void Throw() = 0;
	virtual void Update(int timeElapsed) = 0;
	virtual void recieveMessage(UINT message, WPARAM wParam, LPARAM lParam) = 0;
};
