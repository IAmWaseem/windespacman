#pragma once
#include "BeachBallState.h"
#include "Windows.h"
#include "BeachBall.h"
#include "BeachBallStateMachine.h"

class BeachBallState
{
public:
	BeachBallState(BeachBall * pBeachBall, BeachBallStateMachine * pBeachBallStateMachine);
	~BeachBallState(void);
	virtual void Update(int timeElapsed) = 0;
	virtual void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam) = 0;
protected:
	BeachBall * pBeachBall;
	BeachBallStateMachine * pBeachBallStateMachine;
};
