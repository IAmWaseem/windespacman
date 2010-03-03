#pragma once
#include "Observer.h"
#include "GadgetView.h"
#include "GadgetStateMachine.h"
#include "Location.h"

class Gadget : public Observer
{
public:
	~Gadget(void);
	Gadget(void);
	void recieveMessage(UINT message, WPARAM wParam, LPARAM lParam);
	void Update();
	Location * GetLocation();
	void SetLocation(Location * location);
private:
	GadgetView * pGadgetView;
	GadgetStateMachine * pGadgetStateMachine;
	Location * location;
};
