#pragma once
#include "GadgetState.h"

class PickedUp : public GadgetState
{
public:
	PickedUp(void);
	PickedUp(GadgetStateMachine * pStateMachine, Gadget * gadget);
	~PickedUp(void);
	void Update(int timeElapsed);
	void recieveMessage(UINT message, WPARAM wParam, LPARAM lParam);
	void PickUp();
};
