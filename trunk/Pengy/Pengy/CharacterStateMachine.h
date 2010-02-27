#pragma once
#include "Win.h"
class CharacterState;

class CharacterStateMachine
{
private:
	CharacterState * pCurrentState;

public:

	CharacterState * idle;
	CharacterState * walking;
	CharacterState * jumping;
	CharacterState * falling;

	CharacterStateMachine(void);
	~CharacterStateMachine(void);
	void Up();
	void Down();
	void Left();
	void Right();
	void Spacebar();
	void Throw();
	void Update(int timeElapsed);
	void Transition(CharacterState * pCharacterState);
	void recieveMessage(UINT message, WPARAM wParam, LPARAM lParam);
};
