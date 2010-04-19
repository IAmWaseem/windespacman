#include "MisterFrostState.h"

MisterFrostState::MisterFrostState(MisterFrost * pMisterFrost, MisterFrostStateMachine * pMisterFrostStateMachine)
{
	this->pMisterFrost = pMisterFrost;
	this->pMisterFrostStateMachine = pMisterFrostStateMachine;
}

MisterFrostState::~MisterFrostState(void)
{
}
