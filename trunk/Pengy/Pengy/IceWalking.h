#pragma once
#include "characterstate.h"

class IceWalking : public CharacterState
{
private:
	float distanceToMove;
	long moved;
	float speed;
	void SwapPicture();

public:
	IceWalking(void);
	IceWalking(CharacterStateMachine * pStateMachine);
	void Up();
	void Down();
	void Left();
	void Right();
	void Throw();
	void Spacebar();
	void Update(int timeElapsed);
	void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
};
