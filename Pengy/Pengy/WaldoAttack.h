#pragma once
#include "WaldoState.h"

class WaldoAttack : public WaldoState
{
public:
	WaldoAttack(Waldo * pWaldo, WaldoStateMachine * pWaldoStateMachine);
	~WaldoAttack(void);
	virtual void Update(int timeElapsed);
	virtual void recieveMessage(UINT message, WPARAM wParam, LPARAM lParam);
};
