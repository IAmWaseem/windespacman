#pragma once
#include "WaldoState.h"

class WaldoAttack : public WaldoState
{
public:
	WaldoAttack(Waldo * pWaldo, WaldoStateMachine * pWaldoStateMachine);
	~WaldoAttack(void);
	virtual void Update(int timeElapsed);
	virtual void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
private:
	float speed;
	bool IsPengyOnMySurface();
	bool IsPengyTooFarAway();
	void Throw();
	int throws;
	int throwsInterval;
	int RandomIntBetween(int a, int b);
};
