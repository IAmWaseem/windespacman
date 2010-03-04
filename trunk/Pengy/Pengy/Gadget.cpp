#include "Gadget.h"

Gadget::Gadget(int id, Location * location, GadgetView::GadgetImage gadgetImage)
{
	pGadgetView = new GadgetView(gadgetImage, this);
	pGadgetView->registerToGraphics();

	this->location = location;

	pGadgetStateMachine = new GadgetStateMachine(this);
	this->id = id;
	isRemoved = false;
	this->gadgetImage = gadgetImage;
}

int Gadget::GetId()
{
	return id;
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

void Gadget::Remove()
{
	pGadgetView->unRegisterToGraphics();
	delete pGadgetView;
	delete pGadgetStateMachine;
	isRemoved = true;
}

bool Gadget::IsRemoved()
{
	return isRemoved;
}

GadgetView::GadgetImage Gadget::GetGadgetImage()
{
	return this->gadgetImage;
}
