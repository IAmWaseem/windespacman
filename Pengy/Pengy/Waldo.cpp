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

	this->superWaldo = isSuper;
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
	this->superWaldo = false;
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
	this->superWaldo = false;
}

Waldo::~Waldo(void)
{
	pView->UnRegisterToGraphics();
	delete pView;
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

	if(LocationInWaldoX(pPengyLocation, pLocation) && LocationInWaldoY(pPengyLocation, pLocation))
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
			this->pView->UnRegisterToGraphics();
			MessageQueue::Instance()->SendMessage(CM_WALDO_KILLED, NULL, NULL);
			this->isAlive = false;
			delete this->pLocation;
			delete this->pWaldoStateMachine;
			delete this->pView;

			//extra waldo zodat je naar volgend level gaat
			if(superWaldo)
			{
				//MessageQueue::Instance()->SendMessage(CM_LEVEL_END, NULL, NULL);
				EnemyFactory::SendMessagesToChildren = false;
				MessageQueue::Instance()->SendMessage(CM_LEVEL_START, NULL, NULL);
				//MessageQueue::Instance()->SendMessage(CM_LEVEL_BEGIN, NULL, NULL);
			}
		}
		else
		{
			MessageQueue::Instance()->SendMessage(CM_CHARACTER_KILLED, NULL, NULL);
		}
	}
}

bool Waldo::LocationInWaldoX(Location * pplocationPengy, Location * pLocationWaldo)
{
	bool inGadget = false;
	if(pLocationWaldo->X <= pplocationPengy->X && (pLocationWaldo->X + pLocationWaldo->width) >= (pplocationPengy->X + pplocationPengy->width))
	{
		inGadget = true;
	}
	if(pLocationWaldo->X >= pplocationPengy->X && (pLocationWaldo->X + pLocationWaldo->width) <= (pplocationPengy->X + pplocationPengy->width))
	{
		inGadget = true;
	}
	if(pLocationWaldo->X <= pplocationPengy->X && (pLocationWaldo->X + pLocationWaldo->width) <= (pplocationPengy->X + pplocationPengy->width) && (pLocationWaldo->X + pLocationWaldo->width) > pplocationPengy->X)
	{
		inGadget = true;
	}
	if(pLocationWaldo->X >= pplocationPengy->X && pLocationWaldo->X <= (pplocationPengy->X + pplocationPengy->width) && (pLocationWaldo->X + pLocationWaldo->width) >= (pplocationPengy->X + pplocationPengy->width))
	{
		inGadget = true;
	}
	return inGadget;
}

bool Waldo::LocationInWaldoY(Location * plocationPengy, Location * pLocationWaldo)
{
	bool inGadget = false;
	if(pLocationWaldo->Y  >= plocationPengy->Y && (pLocationWaldo->Y + pLocationWaldo->height) <= (plocationPengy->Y + plocationPengy->height))
	{
		inGadget = true;
	}
	if(pLocationWaldo->Y  <= plocationPengy->Y && (pLocationWaldo->Y + pLocationWaldo->height) >= (plocationPengy->Y + plocationPengy->height))
	{
		inGadget = true;
	}
	if(plocationPengy->Y >= pLocationWaldo->Y && plocationPengy->Y <= (pLocationWaldo->Y + pLocationWaldo->height))
	{
		inGadget = true;
	}
	if((plocationPengy->Y + plocationPengy->height) >= pLocationWaldo->Y && (plocationPengy->Y + plocationPengy->height) <= (pLocationWaldo->Y + pLocationWaldo->height))
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
