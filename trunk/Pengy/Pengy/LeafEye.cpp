#include "LeafEye.h"
#include "LeafEyeView.h"
#include "LeafEyeStateMachine.h"
#include "messages.h"

LeafEye::~LeafEye(void)
{
}

LeafEye::LeafEye(Surface * pSurface) : Enemy(pSurface)
{
	pView=new LeafEyeView(this);
	pLeafEyeStateMachine = new LeafEyeStateMachine(this);
	pView->RegisterToGraphics();
	this->pLocation->width = 304;
	this->pLocation->height = 350;

	this->pLocation->X = pSurface->xTo - this->pLocation->width;
	this->pLocation->Y = pSurface->yFrom - this->pLocation->height;
	this->direction = Direction::Down;
	this->health = 500;
}

void LeafEye::ReceiveMessageInternal(UINT message, WPARAM wParam, LPARAM lParam) {
	if(!this->isAlive)
		return;
	switch(message)
	{
	case CM_UPDATE:
		CheckCollision();
		break;
	}
	if(this->isAlive)
		this->pLeafEyeStateMachine->ReceiveMessage(message, wParam, lParam);
}

void LeafEye::CheckCollision()
{
	if(LocationInEnemyX(pPengyLocation, pLocation) && LocationInEnemyY(pPengyLocation, pLocation))
	{		
		MessageQueue::Instance()->SendMessage(CM_CHARACTER_KILLED, NULL, NULL);
	}
}

void LeafEye::SetLocation(Location * pLocation)
{
	this->pLocation = pLocation;
}