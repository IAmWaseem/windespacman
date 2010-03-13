#include "Waldo.h"
#include "WaldoView.h"
#include "WaldoStateMachine.h"
#include "MessageQueue.h"

Waldo::Waldo(Surface * pSurface, int x) : Enemy(pSurface)
{
	RandomDirection();
	
	this->pView = new WaldoView(this);
	this->pView->registerToGraphics();

	this->pLocation->width = 60;
	this->pLocation->height = 60;

	this->pLocation->X = x;
	this->pLocation->Y = pSurface->yFrom - this->pLocation->height;

	this->pWaldoStateMachine = new WaldoStateMachine(this);
	pWaldoStateMachine->Transition(pWaldoStateMachine->pWander);

	this->isVulnerable = false;
	this->pengyJumping = false;
}

Waldo::Waldo(Surface * pSurface) : Enemy(pSurface)
{
	RandomDirection();

	this->pView = new WaldoView(this);
	this->pView->registerToGraphics();

	this->pLocation->width = 60;
	this->pLocation->height = 60;

	this->pLocation->X = (int)((0.5 * (pSurface->xFrom + pSurface->xTo) - (0.5*this->pLocation->width)));
	this->pLocation->Y = pSurface->yFrom - this->pLocation->height;

	this->pWaldoStateMachine = new WaldoStateMachine(this);
	pWaldoStateMachine->Transition(pWaldoStateMachine->pPatrol);

	this->isVulnerable = false;
	this->pengyJumping = false;
}

Waldo::~Waldo(void)
{
	pView->unRegisterToGraphics();
	delete pView;
}

void Waldo::recieveMessageInternal(UINT message, WPARAM wParam, LPARAM lParam)
{
	if(!this->isAlive)
		return;

	switch(message)
	{

	case CM_UPDATE:
		CheckPengyCollision();
		break;

	case CM_CHARACTER_JUMP_Y_FROM_TO:
		this->pengyJumping = true;
		break;

	case CM_CHARACTER_IS_FALLING:
	case CM_CHARACTER_FALL_Y_FROM_TO:
		if(this->pengyJumping)
			this->isVulnerable = true;
		else
			this->isVulnerable = false;
		break;

	case CM_CHARACTER_IS_STANDING:
		this->isVulnerable = false;
		this->pengyJumping = false;
		break;
	}
	if(this->isAlive)
		this->pWaldoStateMachine->recieveMessage(message, wParam, lParam);
}


void Waldo::CheckPengyCollision()
{
	bool collision = false;
	if(LocationInWaldoX(pPengyLocation, pLocation) && LocationInWaldoY(pPengyLocation, pLocation))
	{
		collision = true;
	}

	if(collision)
	{
		if(this->isVulnerable)
		{
			this->pView->unRegisterToGraphics();
			MessageQueue::Instance()->SendMessage(CM_WALDO_KILLED, NULL, NULL);
			this->isAlive = false;
			delete this->pLocation;
			delete this->pWaldoStateMachine;
			delete this->pView;
		}
		else
		{
			MessageQueue::Instance()->SendMessage(CM_CHARACTER_KILLED, NULL, NULL);
		}
	}
}

bool Waldo::LocationInWaldoX(Location * locationPengy, Location * locationGadget)
{
	bool inGadget = false;
	if(locationGadget->X <= locationPengy->X && (locationGadget->X + locationGadget->width) >= (locationPengy->X + locationPengy->width))
	{
		inGadget = true;
	}
	if(locationGadget->X >= locationPengy->X && (locationGadget->X + locationGadget->width) <= (locationPengy->X + locationPengy->width))
	{
		inGadget = true;
	}
	if(locationGadget->X <= locationPengy->X && (locationGadget->X + locationGadget->width) <= (locationPengy->X + locationPengy->width) && (locationGadget->X + locationGadget->width) > locationPengy->X)
	{
		inGadget = true;
	}
	if(locationGadget->X >= locationPengy->X && locationGadget->X <= (locationPengy->X + locationPengy->width) && (locationGadget->X + locationGadget->width) >= (locationPengy->X + locationPengy->width))
	{
		inGadget = true;
	}
	return inGadget;
}

bool Waldo::LocationInWaldoY(Location * locationPengy, Location * locationGadget)
{
	bool inGadget = false;
	if(locationGadget->Y  >= locationPengy->Y && (locationGadget->Y + locationGadget->height) <= (locationPengy->Y + locationPengy->height))
	{
		inGadget = true;
	}
	if(locationGadget->Y  <= locationPengy->Y && (locationGadget->Y + locationGadget->height) >= (locationPengy->Y + locationPengy->height))
	{
		inGadget = true;
	}
	if(locationPengy->Y >= locationGadget->Y && locationPengy->Y <= (locationGadget->Y + locationGadget->height))
	{
		inGadget = true;
	}
	if((locationPengy->Y + locationPengy->height) >= locationGadget->Y && (locationPengy->Y + locationPengy->height) <= (locationGadget->Y + locationGadget->height))
	{
		inGadget = true;
	}
	return inGadget;
}

void Waldo::RandomDirection()
{
	int randomNumber = rand() % 10 + 1;
	if(randomNumber <=5)
		this->direction = Direction::Right;
	else
		this->direction = Direction::Left;
}
