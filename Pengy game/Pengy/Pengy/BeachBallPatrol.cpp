#include "BeachBallPatrol.h"
#include "math.h"
#include "messages.h"

BeachBallPatrol::BeachBallPatrol(BeachBall * pBeachBall, BeachBallStateMachine * pBeachBallStateMachine):BeachBallState(pBeachBall, pBeachBallStateMachine)
{
	this->speed = 0.3f;
}


BeachBallPatrol::~BeachBallPatrol(void)
{
}

void BeachBallPatrol::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
{
	int timeElapsed;

	switch(message) {
		case CM_UPDATE:
		timeElapsed = wParam;
		this->Update(timeElapsed);
		break;
	}
}

void BeachBallPatrol::Update(int timeElapsed) 
{
	Location * pBeachBallLocation = pBeachBall->GetLocation();
	Surface * pOnSurface = pBeachBall->GetOnSurface();
	
	int surfaceWidth = pOnSurface->xFrom - pOnSurface->xTo;

	if((pBeachBallLocation->X - pOnSurface->xFrom) < -1 && pBeachBall->GetDirection() == Direction::Left)
	{
		pBeachBallLocation->X = pOnSurface->xFrom + 5;
	}

	else if(((pBeachBallLocation->X + pBeachBallLocation->width) - pOnSurface->xTo) > 1 && pBeachBall->GetDirection() == Direction::Right)
	{
		pBeachBallLocation->X = (pOnSurface->xTo - pBeachBallLocation->width) - 5;
	}
	else
	{
		int distanceToRight = fabs(pOnSurface->xTo - (pBeachBallLocation->X + pBeachBallLocation->width));
		int distanceToLeft = fabs(pOnSurface->xFrom - pBeachBallLocation->X);
		int distanceToPengy = fabs(this->pBeachBall->GetPengyLocation()->X - pBeachBallLocation->X);
		float distanceMoved = timeElapsed * this->speed;
		if(distanceToRight < 150 && pBeachBall->GetDirection() == Direction::Right)
		{
			pBeachBall->SetDirection(Direction::Left);
			if(distanceToPengy < 500)
			{
				pBeachBallStateMachine->Transition(pBeachBallStateMachine->pAttack);
			}

		}
		else if(distanceToLeft < 10 && pBeachBall->GetDirection() == Direction::Left)
		{
			pBeachBall->SetDirection(Direction::Right);
			if(distanceToPengy < 500)
			{
				pBeachBallStateMachine->Transition(pBeachBallStateMachine->pAttack);
			}
		}

		switch(pBeachBall->GetDirection())
		{
		case Direction::Left:
			pBeachBall->GetLocation()->X -= distanceMoved;
			break;

		case Direction::Right:
			pBeachBall->GetLocation()->X += distanceMoved;
			break;
		}
	}
}