#include "GadgetStateMachine.h"
#include "Available.h"
#include "PickedUp.h"

GadgetStateMachine::GadgetStateMachine(void)
{
}

GadgetStateMachine::GadgetStateMachine(Gadget * gadget)
{
	available = new Available(this, gadget);
	pickedUp = new PickedUp(this, gadget);
	pCurrentState = available;
}

GadgetStateMachine::~GadgetStateMachine(void)
{
	delete available;
	delete pickedUp;
}

void GadgetStateMachine::Update(int timeElapsed) 
{
}

void GadgetStateMachine::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	pCurrentState->recieveMessage(message, wParam, lParam);
}

void GadgetStateMachine::Transition(GadgetState * pGadgetState)
{
	this->pCurrentState = pGadgetState;
}