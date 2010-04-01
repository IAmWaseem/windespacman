#include "MisterFrostPatrol.h"
#include "math.h"
#include "messages.h"

MisterFrostPatrol::MisterFrostPatrol(MisterFrost * pMisterFrost, MisterFrostStateMachine * pMisterFrostStateMachine):MisterFrostState(pMisterFrost, pMisterFrostStateMachine)
{
	this->speed = 0.3f;
}


MisterFrostPatrol::~MisterFrostPatrol(void)
{
}

void MisterFrostPatrol::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
{
	int timeElapsed;

	switch(message) {
		case CM_UPDATE:
		timeElapsed = wParam;
		this->Update(timeElapsed);
		break;
	}
}

void MisterFrostPatrol::Update(int timeElapsed) 
{
	Location * pMisterFrostLocation = pMisterFrost->GetLocation();
	Surface * pOnSurface = pMisterFrost->GetOnSurface();
	int distanceToPengy = fabs(this->pMisterFrost->GetPengyLocation()->X - pMisterFrostLocation->X);
	
	if(pMisterFrost->GetDirection() == Direction::Up)
	{
		if((pMisterFrostLocation->Y + pMisterFrostLocation->height) - pOnSurface->yFrom + 150 >= 150)
		{
			pMisterFrost->SetDirection(Direction::Down);
			pMisterFrostLocation->Y = pMisterFrostLocation->Y - 3;
		}
		else
			pMisterFrostLocation->Y = pMisterFrostLocation->Y + 3;
		if(distanceToPengy < 500)
		{
			pMisterFrostStateMachine->Transition(pMisterFrostStateMachine->pAttack);
		}
	}
	else if(pMisterFrost->GetDirection() == Direction::Down)
	{
		if((pMisterFrostLocation->Y + pMisterFrostLocation->height) - pOnSurface->yFrom + 150 <= 0)
		{
			pMisterFrost->SetDirection(Direction::Up);
			pMisterFrostLocation->Y = pMisterFrostLocation->Y + 3;
		}
		else
			pMisterFrostLocation->Y = pMisterFrostLocation->Y - 3;
		if(distanceToPengy < 500)
		{
			pMisterFrostStateMachine->Transition(pMisterFrostStateMachine->pAttack);
		}
	}
}