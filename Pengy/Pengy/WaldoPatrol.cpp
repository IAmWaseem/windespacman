#include "WaldoPatrol.h"
#include "math.h"

WaldoPatrol::WaldoPatrol(Waldo * pWaldo, WaldoStateMachine * pWaldoStateMachine):WaldoState(pWaldo, pWaldoStateMachine)
{
	this->speed = 0.06f;
}


WaldoPatrol::~WaldoPatrol(void)
{
}

void WaldoPatrol::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
{
	int timeElapsed;

	switch(message) {
		case CM_UPDATE:
		timeElapsed = wParam;
		this->Update(timeElapsed);
		break;
	}
}

void WaldoPatrol::Update(int timeElapsed) 
{
	Location * pWaldoLocation = pWaldo->GetLocation();
	Surface * pOnSurface = pWaldo->GetOnSurface();
	

	int surfaceWidth = pOnSurface->xFrom - pOnSurface->xTo;

	if((pWaldoLocation->X - pOnSurface->xFrom) < -1 && pWaldo->GetDirection() == Direction::Left)
	{
		pWaldoLocation->X = pOnSurface->xFrom + 5;
	}

	else if(((pWaldoLocation->X + pWaldoLocation->width) - pOnSurface->xTo) > 1 && pWaldo->GetDirection() == Direction::Right)
	{
		pWaldoLocation->X = (pOnSurface->xTo - pWaldoLocation->width) - 5;
	}
	else
	{
		int distanceToRight = fabs(pOnSurface->xTo - (pWaldoLocation->X + pWaldoLocation->width));
		int distanceToLeft = fabs(pOnSurface->xFrom - pWaldoLocation->X);
		float distanceMoved = timeElapsed * this->speed;
		if(distanceToRight < 1 && pWaldo->GetDirection() == Direction::Right)
			pWaldo->SetDirection(Direction::Left);
		else if(distanceToLeft < 1 && pWaldo->GetDirection() == Direction::Left)
			pWaldo->SetDirection(Direction::Right);

		switch(pWaldo->GetDirection())
		{
		case Direction::Left:
			pWaldo->GetLocation()->X -= distanceMoved;
			break;

		case Direction::Right:
			pWaldo->GetLocation()->X += distanceMoved;
			break;
		}
	}
}