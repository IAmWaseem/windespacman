#pragma once
#include "Win.h"
class CharacterState;

class CharacterStateMachine
{
private:
	CharacterState * pCurrentState;

public:

	CharacterState * pIdle;
	CharacterState * pWalking;
	CharacterState * pJumping;
	CharacterState * pFalling;
	CharacterState * pSliding;
	CharacterState * pIceWalking;

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
	void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
};
