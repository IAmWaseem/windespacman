#include "BeachBall.h"
#include "BeachBallView.h"
#include "BeachBallStateMachine.h"

BeachBall::~BeachBall(void)
{
}

BeachBall::BeachBall(Surface * pSurface) : Enemy(pSurface)
{
	pView=new BeachBallView(this);
	pBeachBallStateMachine = new BeachBallStateMachine(this);
	pView->RegisterToGraphics();
	this->pLocation->width = 301;
	this->pLocation->height = 207;

	this->pLocation->X = pSurface->xTo - this->pLocation->width;
	this->pLocation->Y = pSurface->yFrom - this->pLocation->height;
	this->direction = Direction::Left;
}

void BeachBall::ReceiveMessageInternal(UINT message, WPARAM wParam, LPARAM lParam) {
	if(this->isAlive)
		this->pBeachBallStateMachine->ReceiveMessage(message, wParam, lParam);
}