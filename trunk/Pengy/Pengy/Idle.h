#pragma once
#include "characterstate.h"

class Idle : public CharacterState
{
public:
	Idle(void);
	Idle(CharacterStateMachine * pStateMachine);
	void Up();
	void Down();
	void Left();
	void Right();
	void Throw();
	void Spacebar();
	void Update(int timeElapsed);
	void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
};
