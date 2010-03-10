#include "Waldo.h"
#include "WaldoView.h"

Waldo::Waldo(Location * location)
{
	this->location = location;
	this->waldoView = new WaldoView(this);
	this->waldoView->registerToGraphics();
}

Waldo::Waldo(Surface * surface)
{
	this->location->X = (int)(0.5 * (surface->xFrom + surface->xTo));
	this->location->Y = surface->yFrom - 60;
}

Waldo::~Waldo(void)
{
}

void Waldo::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{

}

Location * Waldo::GetLocation()
{
	return location;
}
