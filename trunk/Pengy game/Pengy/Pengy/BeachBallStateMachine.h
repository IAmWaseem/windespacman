#pragma once
#include "Windows.h"

class BeachBall; 

class BeachBallState;

class BeachBallStateMachine
{
public:
	BeachBallStateMachine(BeachBall * pBeachBall);
	~BeachBallStateMachine(void);
	void Update(int timeElapsed);
	void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
	void Transition(BeachBallState * pBeachBallState);

	BeachBallState * pAttack;
	BeachBallState * pPatrol;
private:
	BeachBallState * pCurrentState;
};
