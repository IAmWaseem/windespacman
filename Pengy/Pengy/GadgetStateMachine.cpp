#include "GadgetStateMachine.h"
#include "Available.h"
#include "PickedUp.h"

GadgetStateMachine::GadgetStateMachine(void)
{
}

GadgetStateMachine::GadgetStateMachine(Gadget * gadget)
{
	pAvailable = new Available(this, gadget);
	pPickedUp = new PickedUp(this, gadget);
	pCurrentState = pAvailable;
}

GadgetStateMachine::~GadgetStateMachine(void)
{
	delete pAvailable;
	delete pPickedUp;
}

void GadgetStateMachine::Update(int timeElapsed) 
{
}

void GadgetStateMachine::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	pCurrentState->ReceiveMessage(message, wParam, lParam);
}

void GadgetStateMachine::Transition(GadgetState * pGadgetState)
{
	this->pCurrentState = pGadgetState;
}