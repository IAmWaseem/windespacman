#include "GadgetState.h"

GadgetState::GadgetState(void)
{
}

GadgetState::~GadgetState(void)
{
}

GadgetState::GadgetState(GadgetStateMachine * pStateMachine, Gadget * gadget)  {
	this->pStateMachine = pStateMachine;
	this->pGadget = gadget;
}
