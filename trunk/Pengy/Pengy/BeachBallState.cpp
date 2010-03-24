#include "BeachBallState.h"

BeachBallState::BeachBallState(BeachBall * pBeachBall, BeachBallStateMachine * pBeachBallStateMachine)
{
	this->pBeachBall = pBeachBall;
	this->pBeachBallStateMachine = pBeachBallStateMachine;
}

BeachBallState::~BeachBallState(void)
{
}
