#include "WaldoWander.h"
#include "math.h"
#include "messages.h"

WaldoWander::WaldoWander(Waldo * pWaldo, WaldoStateMachine * pWaldoStateMachine):WaldoState(pWaldo, pWaldoStateMachine)
{
	distanceToWander = 0;
	distanceWandered = 0;
	speed = 0.06f;
}

WaldoWander::~WaldoWander(void)
{
}


void WaldoWander::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
{
	int timeElapsed;
	switch(message) 
	{
	case CM_UPDATE:
		timeElapsed = wParam;
		this->Update(timeElapsed);
		break;
	}
}

void WaldoWander::Update(int timeElapsed) 
{
	int distanceToPengy = fabs((pWaldo->GetPengyLocation()->X + 0.5*pWaldo->GetPengyLocation()->width) - (pWaldo->GetLocation()->X + 0.5*(pWaldo->GetLocation()->width)));
	if(distanceToPengy < 120)
	{
		this->pWaldoStateMachine->Transition(this->pWaldoStateMachine->pAttack);
	}

	if(distanceToWander < 2)
	{
		if(pWaldo->GetDirection() == Direction::Right) pWaldo->SetDirection(Direction::Left);
		else pWaldo->SetDirection(Direction::Right);
		int maxDistanceToWander = 0;
		switch(pWaldo->GetDirection())
		{
		case Direction::Right:
			maxDistanceToWander = pWaldo->GetOnSurface()->xTo - (pWaldo->GetLocation()->X + pWaldo->GetLocation()->width);
			break;
		case Direction::Left:
			maxDistanceToWander = pWaldo->GetLocation()->X - pWaldo->GetOnSurface()->xFrom;
			break;
		}
		maxDistanceToWander -= 2;
		distanceToWander = rand() % maxDistanceToWander + 1;
	}
	else
	{
		float distanceMoved = speed * timeElapsed;
		if(distanceMoved >= distanceToWander)
			distanceMoved = distanceToWander;
		distanceToWander -= distanceMoved;
		switch(pWaldo->GetDirection())
		{
		case Direction::Right:
			pWaldo->GetLocation()->X += distanceMoved;
			break;
		case Direction::Left:
			pWaldo->GetLocation()->X -= distanceMoved;
			break;
		}
	}
}