#include "MisterFrost.h"
#include "MisterFrostView.h"
#include "MisterFrostStateMachine.h"
#include "messages.h"

MisterFrost::~MisterFrost(void)
{
}

MisterFrost::MisterFrost(Surface * pSurface) : Enemy(pSurface)
{
	pView=new MisterFrostView(this);
	pMisterFrostStateMachine = new MisterFrostStateMachine(this);
	pView->RegisterToGraphics();
	this->pLocation->width = 301;
	this->pLocation->height = 207;

	this->pLocation->X = pSurface->xTo - this->pLocation->width;
	this->pLocation->Y = pSurface->yFrom - this->pLocation->height;
	this->direction = Direction::Down;
	this->health = 500;
}

void MisterFrost::ReceiveMessageInternal(UINT message, WPARAM wParam, LPARAM lParam) {
	if(!this->isAlive)
		return;
	switch(message)
	{
	case CM_UPDATE:
		CheckCollision();
		break;
	}
	if(this->isAlive)
		this->pMisterFrostStateMachine->ReceiveMessage(message, wParam, lParam);
}

void MisterFrost::CheckCollision()
{
	if(LocationInEnemyX(pPengyLocation, pLocation) && LocationInEnemyY(pPengyLocation, pLocation))
	{		
		MessageQueue::Instance()->SendMessage(CM_CHARACTER_KILLED, NULL, NULL);
	}
}