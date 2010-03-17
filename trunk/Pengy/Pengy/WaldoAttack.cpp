#include "WaldoAttack.h"
#include "math.h"
#include "messages.h"

WaldoAttack::WaldoAttack(Waldo * pWaldo, WaldoStateMachine * pWaldoStateMachine):WaldoState(pWaldo, pWaldoStateMachine)
{
	this->speed = 0.10f;
}


WaldoAttack::~WaldoAttack(void)
{
}

void WaldoAttack::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
{
	int timeElapsed;

	switch(message) {
		case CM_UPDATE:
		timeElapsed = wParam;
		this->Update(timeElapsed);
		break;
	}
}

void WaldoAttack::Update(int timeElapsed) 
{
	if(IsPengyOnMySurface() && !IsPengyTooFarAway())
	{
		Location * pPengyLocation = pWaldo->GetPengyLocation();
		Location * pWaldoLocation = pWaldo->GetLocation();
		int pengyX = pPengyLocation->X + (0.5 * pPengyLocation->width);
		int waldoX = pWaldoLocation->X + (0.5 * pWaldoLocation->width);
		float distanceMoved = speed * timeElapsed;
		if(pengyX > waldoX)
		{
			if(pWaldo->GetDirection() != Direction::Right) pWaldo->SetDirection(Direction::Right);
			pWaldoLocation->X += distanceMoved;
		}
		else if (pengyX < waldoX)
		{
			if(pWaldo->GetDirection() != Direction::Left) pWaldo->SetDirection(Direction::Left);
			pWaldoLocation->X -= distanceMoved;

		}
	}
	else
	{
		this->pWaldoStateMachine->Transition(this->pWaldoStateMachine->pWander);
	}
}

bool WaldoAttack::IsPengyOnMySurface()
{
	Location * pPengyLocation = pWaldo->GetPengyLocation();
	Location * pWaldoLocation = pWaldo->GetLocation();
	Surface * pOnSurface = pWaldo->GetOnSurface();
	if(pPengyLocation->X >= pOnSurface->xFrom && pPengyLocation->X <= pOnSurface->xTo)
		return true;
	else return false;
}

bool WaldoAttack::IsPengyTooFarAway()
{
	Location * pPengyLocation = pWaldo->GetPengyLocation();
	Location * pWaldoLocation = pWaldo->GetLocation();
	int distanceToPengy = fabs((pWaldo->GetPengyLocation()->X + 0.5*pWaldo->GetPengyLocation()->width) - (pWaldo->GetLocation()->X + 0.5*(pWaldoLocation->width)));
	int distanceToPengyY = fabs((pWaldo->GetPengyLocation()->Y + 0.5*pWaldo->GetPengyLocation()->height) - (pWaldo->GetLocation()->Y + 0.5*(pWaldoLocation->height)));
	
	if(distanceToPengyY > 100)
		return true;

	if(distanceToPengy <= 240)
		return false;

	return true;
}