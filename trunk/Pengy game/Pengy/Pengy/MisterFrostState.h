#pragma once
#include "MisterFrostState.h"
#include "Windows.h"
#include "MisterFrost.h"
#include "MisterFrostStateMachine.h"

class MisterFrostState
{
public:
	MisterFrostState(MisterFrost * pMisterFrost, MisterFrostStateMachine * pMisterFrostStateMachine);
	~MisterFrostState(void);
	virtual void Update(int timeElapsed) = 0;
	virtual void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam) = 0;
protected:
	MisterFrost * pMisterFrost;
	MisterFrostStateMachine * pMisterFrostStateMachine;
};
