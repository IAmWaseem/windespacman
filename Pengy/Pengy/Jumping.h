#pragma once
#include "characterstate.h"

class Jumping : public CharacterState
{
private:
	float upwardVelocity;
	Direction direction;
	float distanceToMove;
	float speed;

public:
	Jumping(void);
	Jumping(CharacterStateMachine * pStateMachine);
	void Up();
	void Down();
	void Left();
	void Right();
	void Throw();
	void Spacebar();
	void Update(int timeElapsed);
	void recieveMessage(UINT message, WPARAM wParam, LPARAM lParam);
};
