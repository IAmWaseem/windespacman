#include "MisterFrostStateMachine.h"
#include "MisterFrostAttack.h"
#include "MisterFrostPatrol.h"
#include "MisterFrostState.h"
#include "MisterFrost.h"

MisterFrostStateMachine::MisterFrostStateMachine(MisterFrost * pMisterFrost)
{
	this->pAttack = new MisterFrostAttack(pMisterFrost, this);
	this->pPatrol = new MisterFrostPatrol(pMisterFrost, this);
	this->pCurrentState = this->pPatrol;
}

MisterFrostStateMachine::~MisterFrostStateMachine(void)
{
}

void MisterFrostStateMachine::Transition(MisterFrostState * pMisterFrostState)
{
	this->pCurrentState = pMisterFrostState;
}

void MisterFrostStateMachine::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	this->pCurrentState->ReceiveMessage(message, wParam, lParam);
}