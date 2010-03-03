#include "PickedUp.h"
#include "Gadget.h"

PickedUp::PickedUp(void)
{
}

PickedUp::~PickedUp(void)
{
}

PickedUp::PickedUp(GadgetStateMachine * pStateMachine, Gadget * gadget) : GadgetState(pStateMachine, gadget)
{
}

void PickedUp::Update(int timeElapsed) {
}

void PickedUp::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
{
}

void PickedUp::PickUp() 
{
}