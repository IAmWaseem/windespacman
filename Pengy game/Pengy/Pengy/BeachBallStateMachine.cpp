#include "BeachBallStateMachine.h"
#include "BeachBallAttack.h"
#include "BeachBallPatrol.h"
#include "BeachBallState.h"
#include "BeachBall.h"

BeachBallStateMachine::BeachBallStateMachine(BeachBall * pBeachBall)
{
	this->pAttack = new BeachBallAttack(pBeachBall, this);
	this->pPatrol = new BeachBallPatrol(pBeachBall, this);
	this->pCurrentState = this->pPatrol;
}

BeachBallStateMachine::~BeachBallStateMachine(void)
{
}

void BeachBallStateMachine::Transition(BeachBallState * pBeachBallState)
{
	this->pCurrentState = pBeachBallState;
}

void BeachBallStateMachine::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	this->pCurrentState->ReceiveMessage(message, wParam, lParam);
}