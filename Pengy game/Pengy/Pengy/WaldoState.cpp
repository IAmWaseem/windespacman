#include "WaldoState.h"

WaldoState::WaldoState(Waldo * pWaldo, WaldoStateMachine * pWaldoStateMachine)
{
	this->pWaldo = pWaldo;
	this->pWaldoStateMachine = pWaldoStateMachine;
}

WaldoState::~WaldoState(void)
{
}
