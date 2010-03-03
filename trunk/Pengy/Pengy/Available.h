#pragma once
#include "GadgetState.h"

class Available : public GadgetState
{
public:
	Available(void);
	Available(GadgetStateMachine * pStateMachine, Gadget * gadget);
	~Available(void);
	void Update(int timeElapsed);
	void recieveMessage(UINT message, WPARAM wParam, LPARAM lParam);
	void PickUp();
	bool LocationInGadgetX(Location * locationPengy, Location * locationGadget);
	bool LocationInGadgetY(Location * locationPengy, Location * locationGadget);
};
