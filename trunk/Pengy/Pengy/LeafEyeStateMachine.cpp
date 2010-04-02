#include "LeafEyeStateMachine.h"
#include "LeafEyeAttack.h"
#include "LeafEyePatrol.h"
#include "LeafEyeState.h"
#include "LeafEye.h"

LeafEyeStateMachine::LeafEyeStateMachine(LeafEye * pLeafEye)
{
	this->pAttack = new LeafEyeAttack(pLeafEye, this);
	this->pPatrol = new LeafEyePatrol(pLeafEye, this);
	this->pCurrentState = this->pPatrol;
}

LeafEyeStateMachine::~LeafEyeStateMachine(void)
{
}

void LeafEyeStateMachine::Transition(LeafEyeState * pLeafEyeState)
{
	this->pCurrentState = pLeafEyeState;
}

void LeafEyeStateMachine::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	this->pCurrentState->ReceiveMessage(message, wParam, lParam);
}