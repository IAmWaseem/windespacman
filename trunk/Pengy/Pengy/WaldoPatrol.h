#pragma once
#include "WaldoState.h"

class WaldoPatrol : public WaldoState
{
public:
	WaldoPatrol(Waldo * pWaldo, WaldoStateMachine * pWaldoStateMachine);
	~WaldoPatrol(void);
	virtual void Update(int timeElapsed);
	virtual void recieveMessage(UINT message, WPARAM wParam, LPARAM lParam);
};
