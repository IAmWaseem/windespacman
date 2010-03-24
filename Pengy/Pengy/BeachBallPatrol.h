#pragma once
#include "BeachBallState.h"

class BeachBallPatrol : public BeachBallState
{
private: 
	float speed;
public:
	BeachBallPatrol(BeachBall * pBeachBall, BeachBallStateMachine * pBeachBallStateMachine);
	~BeachBallPatrol(void);
	virtual void Update(int timeElapsed);
	virtual void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
};
