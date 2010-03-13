#include "Available.h"
#include "Gadget.h"
#include "MessageQueue.h"

Available::Available(void)
{
}

Available::Available(GadgetStateMachine * pStateMachine, Gadget * gadget) : GadgetState(pStateMachine, gadget)
{
}

Available::~Available(void)
{
}

void Available::Update(int timeElapsed) {
}

void Available::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
{
	Location * pFromLocation;
	Location * pToLocation;
	Location * pGadgetLocation = pGadget->GetLocation();
	switch(message) {
		case CM_CHARACTER_MOVE_X_FROM_TO:
		case CM_CHARACTER_FALL_Y_FROM_TO:
		case CM_CHARACTER_JUMP_Y_FROM_TO:
			pFromLocation = (Location*)wParam;
			pToLocation = (Location*)lParam;
			if(LocationInGadgetX(pToLocation, pGadgetLocation) && LocationInGadgetY(pToLocation, pGadgetLocation))
			{
				pStateMachine->Transition(pStateMachine->pPickedUp);
				pStateMachine->pPickedUp->PickUp();
			}
			break;
	}
}

void Available::PickUp() 
{
}

bool Available::LocationInGadgetX(Location * plocationPengy, Location * pLocationGadget)
{
	bool inGadget = false;
	if(pLocationGadget->X <= plocationPengy->X && (pLocationGadget->X + pLocationGadget->width) >= (plocationPengy->X + plocationPengy->width))
	{
		inGadget = true;
	}
	if(pLocationGadget->X >= plocationPengy->X && (pLocationGadget->X + pLocationGadget->width) <= (plocationPengy->X + plocationPengy->width))
	{
		inGadget = true;
	}
	if(pLocationGadget->X <= plocationPengy->X && (pLocationGadget->X + pLocationGadget->width) <= (plocationPengy->X + plocationPengy->width) && (pLocationGadget->X + pLocationGadget->width) > plocationPengy->X)
	{
		inGadget = true;
	}
	if(pLocationGadget->X >= plocationPengy->X && pLocationGadget->X <= (plocationPengy->X + plocationPengy->width) && (pLocationGadget->X + pLocationGadget->width) >= (plocationPengy->X + plocationPengy->width))
	{
		inGadget = true;
	}
	return inGadget;
}

bool Available::LocationInGadgetY(Location * plocationPengy, Location * pLocationGadget)
{
	bool inGadget = false;
	if(pLocationGadget->Y  >= plocationPengy->Y && (pLocationGadget->Y + pLocationGadget->height) <= (plocationPengy->Y + plocationPengy->height))
	{
		inGadget = true;
	}
	if(pLocationGadget->Y  <= plocationPengy->Y && (pLocationGadget->Y + pLocationGadget->height) >= (plocationPengy->Y + plocationPengy->height))
	{
		inGadget = true;
	}
	if(plocationPengy->Y >= pLocationGadget->Y && plocationPengy->Y <= (pLocationGadget->Y + pLocationGadget->height))
	{
		inGadget = true;
	}
	if((plocationPengy->Y + plocationPengy->height) >= pLocationGadget->Y && (plocationPengy->Y + plocationPengy->height) <= (pLocationGadget->Y + pLocationGadget->height))
	{
		inGadget = true;
	}
	return inGadget;
}