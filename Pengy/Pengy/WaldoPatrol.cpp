#include "WaldoPatrol.h"
#include "math.h"

WaldoPatrol::WaldoPatrol(Waldo * pWaldo, WaldoStateMachine * pWaldoStateMachine):WaldoState(pWaldo, pWaldoStateMachine)
{
	this->speed = 0.08f;
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
	int distanceToRight = fabs(pOnSurface->xTo - (pWaldoLocation->X + pWaldoLocation->width));
	int distanceToLeft = fabs(pOnSurface->xFrom - pWaldoLocation->X);
	float distanceMoved = timeElapsed * this->speed;
	if(distanceToRight < 5 && pWaldo->GetDirection() == Direction::Right)
		pWaldo->SetDirection(Direction::Left);
	else if(distanceToLeft < 5 && pWaldo->GetDirection() == Direction::Left)
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