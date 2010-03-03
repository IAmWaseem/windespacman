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

void Available::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
{
	Location * fromLocation;
	Location * toLocation;
	Location * gadgetLocation = pGadget->GetLocation();;
	switch(message) {
		case CM_CHARACTER_MOVE_X_FROM_TO:
		case CM_CHARACTER_FALL_Y_FROM_TO:
		case CM_CHARACTER_JUMP_Y_FROM_TO:
			fromLocation = (Location*)wParam;
			toLocation = (Location*)lParam;
			if(LocationInGadgetX(toLocation, gadgetLocation) && LocationInGadgetY(toLocation, gadgetLocation))
			{
				pStateMachine->Transition(pStateMachine->pickedUp);
				MessageQueue::Inst()->sendMessage(CM_GADGET_GOLDFISH_PICKEDUP, NULL, NULL);
			}
			break;
	}
}

void Available::PickUp() 
{
}

bool Available::LocationInGadgetX(Location * locationPengy, Location * locationGadget)
{
	bool inGadget = false;
	if(locationGadget->X <= locationPengy->X && (locationGadget->X + locationGadget->width) >= (locationPengy->X + locationPengy->width))
	{
		inGadget = true;
	}
	if(locationGadget->X >= locationPengy->X && (locationGadget->X + locationGadget->width) <= (locationPengy->X + locationPengy->width))
	{
		inGadget = true;
	}
	if(locationGadget->X <= locationPengy->X && (locationGadget->X + locationGadget->width) <= (locationPengy->X + locationPengy->width) && (locationGadget->X + locationGadget->width) > locationPengy->X)
	{
		inGadget = true;
	}
	if(locationGadget->X >= locationPengy->X && locationGadget->X <= (locationPengy->X + locationPengy->width) && (locationGadget->X + locationGadget->width) >= (locationPengy->X + locationPengy->width))
	{
		inGadget = true;
	}
	return inGadget;
}

bool Available::LocationInGadgetY(Location * locationPengy, Location * locationGadget)
{
	bool inGadget = false;
	if(locationGadget->Y  >= locationPengy->Y && (locationGadget->Y + locationGadget->height) <= (locationPengy->Y + locationPengy->height))
	{
		inGadget = true;
	}
	if(locationGadget->Y  <= locationPengy->Y && (locationGadget->Y + locationGadget->height) >= (locationPengy->Y + locationPengy->height))
	{
		inGadget = true;
	}
	if(locationPengy->Y >= locationGadget->Y && locationPengy->Y <= (locationGadget->Y + locationGadget->height))
	{
		inGadget = true;
	}
	if((locationPengy->Y + locationPengy->height) >= locationGadget->Y && (locationPengy->Y + locationPengy->height) <= (locationGadget->Y + locationGadget->height))
	{
		inGadget = true;
	}
	return inGadget;
}