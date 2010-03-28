#include "Waldo.h"
#include "WaldoView.h"
#include "WaldoStateMachine.h"
#include "MessageQueue.h"

//extra voor superWaldo
Waldo::Waldo(Surface * pSurface, int x, bool isSuper):Enemy(pSurface)
{
	RandomDirection();
	
	this->pView = new WaldoView(this);
	this->pView->RegisterToGraphics();

	this->pLocation->width = 60;
	this->pLocation->height = 60;

	this->pLocation->X = x;
	this->pLocation->Y = pSurface->yFrom - this->pLocation->height;

	this->pWaldoStateMachine = new WaldoStateMachine(this);
	pWaldoStateMachine->Transition(pWaldoStateMachine->pWander);

	this->isVulnerable = false;

	this->endsLevel = isSuper;
}

Waldo::Waldo(Surface * pSurface, int x) : Enemy(pSurface)
{
	RandomDirection();
	
	this->pView = new WaldoView(this);
	this->pView->RegisterToGraphics();

	this->pLocation->width = 60;
	this->pLocation->height = 60;

	this->pLocation->X = x;
	this->pLocation->Y = pSurface->yFrom - this->pLocation->height;

	this->pWaldoStateMachine = new WaldoStateMachine(this);
	pWaldoStateMachine->Transition(pWaldoStateMachine->pWander);

	this->isVulnerable = false;
	this->endsLevel = false;
}

Waldo::Waldo(Surface * pSurface) : Enemy(pSurface)
{
	RandomDirection();

	this->pView = new WaldoView(this);
	this->pView->RegisterToGraphics();

	this->pLocation->width = 60;
	this->pLocation->height = 60;

	this->pLocation->X = (int)((0.5 * (pSurface->xFrom + pSurface->xTo) - (0.5*this->pLocation->width)));
	this->pLocation->Y = pSurface->yFrom - this->pLocation->height;

	this->pWaldoStateMachine = new WaldoStateMachine(this);
	pWaldoStateMachine->Transition(pWaldoStateMachine->pPatrol);

	this->isVulnerable = false;
	this->endsLevel = false;
}

Waldo::~Waldo(void)
{
}

void Waldo::ReceiveMessageInternal(UINT message, WPARAM wParam, LPARAM lParam)
{
	if(!this->isAlive)
		return;

	switch(message)
	{
	case CM_UPDATE:
		CheckPengyCollision();
		break;

	case CM_CHARACTER_IS_STANDING:
		this->isVulnerable = false;
		break;
	}
	if(this->isAlive)
		this->pWaldoStateMachine->ReceiveMessage(message, wParam, lParam);
}


void Waldo::CheckPengyCollision()
{
	bool collision = false;
	this->isVulnerable = false;

	if(LocationInEnemyX(pPengyLocation, pLocation) && LocationInEnemyY(pPengyLocation, pLocation))
	{		
		collision = true;

		int Pengy = (pPengyLocation->Y + pPengyLocation->height);
		int Waldo = (pLocation->Y);
		if(Pengy >= Waldo - 5 && Pengy <= Waldo + 8)
		{
			this->isVulnerable = true;
		}
	}

	if(collision)
	{
		if(this->isVulnerable)
		{
			DoDamage(100);
		}
		else
		{
			MessageQueue::Instance()->SendMessage(CM_CHARACTER_KILLED, NULL, NULL);
		}
	}
}


void Waldo::RandomDirection()
{
	int randomNumber = rand() % 10 + 1;
	if(randomNumber <=5)
		this->direction = Direction::Right;
	else
		this->direction = Direction::Left;
}
