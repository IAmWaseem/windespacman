#include "Waldo.h"
#include "WaldoView.h"
#include "WaldoStateMachine.h"
#include "MessageQueue.h"

Waldo::Waldo(Location * pLocation)
{
	this->direction = Direction::Right;
	this->pLocation = pLocation;
	this->pWaldoView = new WaldoView(this);
	this->pWaldoView->registerToGraphics();

	this->pWaldoStateMachine = new WaldoStateMachine(this);
	pWaldoStateMachine->Transition(pWaldoStateMachine->pWander);

	this->isVulnerable = false;
}

Waldo::Waldo(Surface * pSurface)
{
	this->pOnSurface = pSurface;
	this->direction = Direction::Right;
	this->pLocation = new Location();
	this->pWaldoView = new WaldoView(this);
	this->pWaldoView->registerToGraphics();

	this->pLocation->width = 60;
	this->pLocation->height = 60;

	this->pLocation->X = (int)((0.5 * (pSurface->xFrom + pSurface->xTo) - (0.5*this->pLocation->width)));
	this->pLocation->Y = pSurface->yFrom - this->pLocation->height;

	this->pWaldoStateMachine = new WaldoStateMachine(this);
	pWaldoStateMachine->Transition(pWaldoStateMachine->pPatrol);

	this->isVulnerable = false;
}

Waldo::~Waldo(void)
{
}

void Waldo::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case CM_UPDATE:
		MessageQueue::Inst()->sendMessage(CM_CHARACTER_GET_LOCATION, NULL, NULL);
		break;
	case CM_CHARACTER_RETURN_LOCATION:
		this->pPengyLocation = (Location*)wParam;
		CheckPengyCollision();
		break;
	}
	this->pWaldoStateMachine->recieveMessage(message, wParam, lParam);
}

Location * Waldo::GetLocation()
{
	return pLocation;
}

Direction Waldo::GetDirection()
{
	return this->direction;
}

Surface * Waldo::GetOnSurface()
{
	return this->pOnSurface;
}

void Waldo::SetDirection(Direction direction)
{
	this->direction = direction;
}

void Waldo::CheckPengyCollision()
{

}
