#pragma once
#include "GadgetState.h"

class Available : public GadgetState
{
public:
	Available(void);
	Available(GadgetStateMachine * pStateMachine, Gadget * gadget);
	~Available(void);
	void Update(int timeElapsed);
	void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
	void PickUp();
	bool LocationInGadgetX(Location * pLocationPengy, Location * pLocationGadget);
	bool LocationInGadgetY(Location * pLocationPengy, Location * pLocationGadget);
};
