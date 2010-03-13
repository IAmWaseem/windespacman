#include "Gadget.h"

Gadget::Gadget(int id, Location * pLocation, GadgetView::GadgetImage gadgetImage)
{
	pGadgetView = new GadgetView(gadgetImage, this);
	pGadgetView->registerToGraphics();

	if(pLocation->width <= 0)
	{
		pLocation->width = 60;
	}
	if(pLocation->height <= 0)
	{
		pLocation->height = 30;
	}
	this->pLocation = pLocation;


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
	pGadgetView->unRegisterToGraphics();
}

void Gadget::Update()
{

}

Location * Gadget::GetLocation()
{
	return pLocation;
}

void Gadget::SetLocation(Location * pLocation)
{
	this->pLocation = pLocation;
}

void Gadget::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam) {
	pGadgetStateMachine->ReceiveMessage(message, wParam, lParam);
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
