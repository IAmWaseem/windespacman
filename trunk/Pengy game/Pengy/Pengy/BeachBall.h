#pragma once
#include "enemy.h"
#include "surface.h"
#include "location.h"

class BeachBallStateMachine;

class View;

class BeachBall : public Enemy
{
public:
	BeachBall(Surface * pSurface);
	~BeachBall(void);
	virtual void ReceiveMessageInternal(UINT message, WPARAM wParam, LPARAM lParam);
private:
	BeachBallStateMachine * pBeachBallStateMachine;
	void CheckCollision();
};
