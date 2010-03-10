#include "Waldo.h"
#include "WaldoView.h"
#include "WaldoStateMachine.h"

Waldo::Waldo(Location * pLocation)
{
	this->pLocation = pLocation;
	this->pWaldoView = new WaldoView(this);
	this->pWaldoView->registerToGraphics();

	this->pWaldoStateMachine = new WaldoStateMachine(this);
	pWaldoStateMachine->Transition(pWaldoStateMachine->pWander);
}

Waldo::Waldo(Surface * pSurface)
{
	this->pLocation = new Location();
	this->pWaldoView = new WaldoView(this);
	this->pWaldoView->registerToGraphics();

	this->pLocation->width = 60;
	this->pLocation->height = 60;

	this->pLocation->X = (int)((0.5 * (pSurface->xFrom + pSurface->xTo) - (0.5*this->pLocation->width)));
	this->pLocation->Y = pSurface->yFrom - this->pLocation->height;

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
	return pLocation;
}
