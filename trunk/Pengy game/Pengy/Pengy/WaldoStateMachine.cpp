#include "WaldoStateMachine.h"
#include "WaldoAttack.h"
#include "WaldoPatrol.h"
#include "WaldoWander.h"
#include "Waldo.h"

WaldoStateMachine::WaldoStateMachine(Waldo * pWaldo)
{
	this->pAttack = new WaldoAttack(pWaldo, this);
	this->pPatrol = new WaldoPatrol(pWaldo, this);
	this->pWander = new WaldoWander(pWaldo, this);
}

WaldoStateMachine::~WaldoStateMachine(void)
{
}

void WaldoStateMachine::Transition(WaldoState * pWaldoState)
{
	this->pCurrentState = pWaldoState;
}

void WaldoStateMachine::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	this->pCurrentState->ReceiveMessage(message, wParam, lParam);
}