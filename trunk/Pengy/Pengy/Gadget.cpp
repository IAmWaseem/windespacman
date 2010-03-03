#include "Gadget.h"

Gadget::Gadget(void)
{
	pGadgetView = new GadgetView(GadgetView::GadgetImage::Goldfish, "res/GadgetRottenFish.bmp", this);
	pGadgetView->registerToGraphics();

	location = new Location();
	location->X = 200;
	location->Y = 300;

	pGadgetStateMachine = new GadgetStateMachine(this);
}

Gadget::~Gadget(void)
{
}

void Gadget::Update()
{

}

Location * Gadget::GetLocation()
{
	return location;
}

void Gadget::SetLocation(Location * location)
{
	this->location = location;
}

void Gadget::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam) {
	pGadgetStateMachine->recieveMessage(message, wParam, lParam);
}
