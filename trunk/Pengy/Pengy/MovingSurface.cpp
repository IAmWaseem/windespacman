#include "MovingSurface.h"

MovingSurface::MovingSurface(void)
{
	this->initMoveUp = false;
	this->isCloud = false;
	this->isSlope = false;
	this->isIce = false;
	this->isSurfaceOfDeath = false;
	this->xFrom = 0;
	this->xTo = 0;
	this->yFrom = 0;
	this->yTo = 20;
	this->firstY = 0;
	this->difY = 20;
	this->speed = 0.10f;
	this->maxDif = 0;
}
MovingSurface::MovingSurface(int FromX, int FromY, int ToX, int ToY, int theMaxDif, bool MoveUp, MovingSurfaceType type)
{
	this->initMoveUp = MoveUp;
	this->isCloud = false;
	this->isSlope = false;
	this->isIce = false;
	this->isSurfaceOfDeath = false;
	this->xFrom = FromX;
	this->xTo = ToX;
	this->yFrom = FromY;
	this->firstY = FromY;
	this->difY = (FromY - ToY);
	this->yTo = ToY;
	this->speed = 0.10f;
	this->maxDif = theMaxDif;
	msView = new MovingSurfaceView(this, type);
	msView->RegisterToGraphics();
}

void MovingSurface::Update(int timeElapsed)
{
	if(maxDif > 0)
	{
		float distanceMoved = timeElapsed * this->speed;
		int distance = 0;
		
		if(initMoveUp)
		{
			distanceMoved = distanceMoved * -1;
		}

		distance = this->yFrom + distanceMoved;

		if(distance <= firstY)
			initMoveUp = false;
		if(distance > firstY + maxDif)
			initMoveUp = true;

		this->yFrom = distance;
		this->yTo = distance + difY;
	}
}
void MovingSurface::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	int timeElapsed;

	switch(message) {
		case CM_UPDATE:
			timeElapsed = wParam;
			this->Update(timeElapsed);
			break;
	}
}

MovingSurface::~MovingSurface(void)
{
	msView->UnRegisterToGraphics();
	MessageQueue::Instance()->Detach(this);
	delete msView;
}
