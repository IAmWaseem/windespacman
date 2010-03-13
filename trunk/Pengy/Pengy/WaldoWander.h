#pragma once
#include "WaldoState.h"

class WaldoWander : public WaldoState
{
private:
	float distanceToWander;
	float distanceWandered;
	float speed;

public:
	WaldoWander(Waldo * pWaldo, WaldoStateMachine * pWaldoStateMachine);
	~WaldoWander(void);
	virtual void Update(int timeElapsed);
	virtual void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
};
