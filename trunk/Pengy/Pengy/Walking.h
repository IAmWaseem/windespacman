#pragma once
#include "characterstate.h"

class Walking : public CharacterState
{
private:
	float distanceToMove;
	float moved;
	float speed;
	void SwapPicture();

public:
	Walking(void);
	Walking(CharacterStateMachine * pStateMachine);
	void Up();
	void Down();
	void Left();
	void Right();
	void Throw();
	void Spacebar();
	void Update(int timeElapsed);
	void recieveMessage(UINT message, WPARAM wParam, LPARAM lParam);
};
