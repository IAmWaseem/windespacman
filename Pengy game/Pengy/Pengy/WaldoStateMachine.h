#pragma once
#include "Windows.h"

class Waldo; 

class WaldoState;

class WaldoStateMachine
{
public:
	WaldoStateMachine(Waldo * pWaldo);
	~WaldoStateMachine(void);
	void Update(int timeElapsed);
	void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
	void Transition(WaldoState * pWaldoState);

	WaldoState * pWander;
	WaldoState * pAttack;
	WaldoState * pPatrol;
private:
	WaldoState * pCurrentState;
};
