#pragma once
#include "characterstate.h"

class Falling : public CharacterState
{
private:
	float downwardVelocity;
	float distanceToMove;
	float speed;

public:
	Falling(void);
	Falling(CharacterStateMachine * pStateMachine);
	void Up();
	void Down();
	void Left();
	void Right();
	void Throw();
	void Spacebar();
	void Update(int timeElapsed);
	void recieveMessage(UINT message, WPARAM wParam, LPARAM lParam);
};
