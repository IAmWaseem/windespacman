#pragma once
#include "WaldoState.h"

class WaldoWander : public WaldoState
{
public:
	WaldoWander(Waldo * pWaldo, WaldoStateMachine * pWaldoStateMachine);
	~WaldoWander(void);
	virtual void Update(int timeElapsed);
	virtual void recieveMessage(UINT message, WPARAM wParam, LPARAM lParam);
};
