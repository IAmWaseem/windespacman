#pragma once
#include "Win.h"
#include "MessageQueue.h"
#include "Gadget.h"

class GadgetStateMachine;

class GadgetState
{
protected:
	GadgetStateMachine * pStateMachine;
	Gadget * pGadget;

public:
	GadgetState(void);
	GadgetState(GadgetStateMachine * pStateMachine, Gadget * gadget);
	~GadgetState(void);
	virtual void Update(int timeElapsed) = 0;
	virtual void PickUp() = 0;
	virtual void recieveMessage(UINT message, WPARAM wParam, LPARAM lParam) = 0;
};
