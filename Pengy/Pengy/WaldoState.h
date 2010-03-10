#pragma once
#include "WaldoState.h"
#include "Windows.h"
#include "Waldo.h"
#include "WaldoStateMachine.h"

class WaldoState
{
public:
	WaldoState(Waldo * pWaldo, WaldoStateMachine * pWaldoStateMachine);
	~WaldoState(void);
	virtual void Update(int timeElapsed) = 0;
	virtual void recieveMessage(UINT message, WPARAM wParam, LPARAM lParam) = 0;
protected:
	Waldo * pWaldo;
	WaldoStateMachine * pWaldoStateMachine;
};
