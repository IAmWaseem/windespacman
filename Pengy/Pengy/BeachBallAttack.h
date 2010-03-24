#pragma once
#include "BeachBallState.h"

class BeachBallAttack : public BeachBallState
{
public:
	BeachBallAttack(BeachBall * pBeachBall, BeachBallStateMachine * pBeachBallStateMachine);
	~BeachBallAttack(void);
	virtual void Update(int timeElapsed);
	virtual void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
private:
	float speed;
	void Throw();
	int throws;
	int throwsInterval;
	int RandomIntBetween(int a, int b);
};
