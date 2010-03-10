#include "Waldo.h"
#include "WaldoView.h"
#include "WaldoStateMachine.h"

Waldo::Waldo(Location * location)
{
	this->location = location;
	this->waldoView = new WaldoView(this);
	this->waldoView->registerToGraphics();

	this->pWaldoStateMachine = new WaldoStateMachine(this);
	pWaldoStateMachine->Transition(pWaldoStateMachine->pWander);
}

Waldo::Waldo(Surface * surface)
{
	location = new Location();
	this->waldoView = new WaldoView(this);
	this->waldoView->registerToGraphics();

	this->location->X = (int)(0.5 * (surface->xFrom + surface->xTo));
	this->location->Y = surface->yFrom - 60;

	this->pWaldoStateMachine = new WaldoStateMachine(this);
	pWaldoStateMachine->Transition(pWaldoStateMachine->pPatrol);
}

Waldo::~Waldo(void)
{
}

void Waldo::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	this->pWaldoStateMachine->recieveMessage(message, wParam, lParam);
}

Location * Waldo::GetLocation()
{
	return location;
}
