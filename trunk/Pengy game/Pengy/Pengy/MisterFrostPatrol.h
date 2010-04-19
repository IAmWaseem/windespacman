#pragma once
#include "MisterFrostState.h"

class MisterFrostPatrol : public MisterFrostState
{
private: 
	float speed;
public:
	MisterFrostPatrol(MisterFrost * pMisterFrost, MisterFrostStateMachine * pMisterFrostStateMachine);
	~MisterFrostPatrol(void);
	virtual void Update(int timeElapsed);
	virtual void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
};
