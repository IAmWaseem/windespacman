#pragma once
#include "Windows.h"

class MisterFrost; 

class MisterFrostState;

class MisterFrostStateMachine
{
public:
	MisterFrostStateMachine(MisterFrost * pMisterFrost);
	~MisterFrostStateMachine(void);
	void Update(int timeElapsed);
	void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
	void Transition(MisterFrostState * pMisterFrostState);

	MisterFrostState * pAttack;
	MisterFrostState * pPatrol;
private:
	MisterFrostState * pCurrentState;
};
