#pragma once
#include "Observer.h"
#include "GadgetView.h"
#include "GadgetStateMachine.h"
#include "Location.h"

class Gadget
{
public:
	~Gadget(void);
	Gadget(int id, Location * location, GadgetView::GadgetImage gadgetImage);
	void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
	void Update();
	Location * GetLocation();
	void SetLocation(Location * location);
	int GetId();
	void Remove();
	bool IsRemoved();
	GadgetView::GadgetImage GetGadgetImage();
private:
	GadgetView * pGadgetView;
	GadgetStateMachine * pGadgetStateMachine;
	Location * location;
	int id;
	bool isRemoved;
	GadgetView::GadgetImage gadgetImage;
};
