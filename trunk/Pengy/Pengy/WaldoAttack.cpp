#include "WaldoAttack.h"
#include "math.h"
#include "messages.h"
#include "weapon.h"
#include <ctime>
#include <cstdlib>
#include "character.h"

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
		Throw();
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

void WaldoAttack::Throw() 
    {	
	if(throws == throwsInterval)
	{
   		Location * pWl = new Location();
		pWl->X = pWaldo->GetLocation()->X;
		pWl->Y = pWaldo->GetLocation()->Y + (pWaldo->GetLocation()->height/2);

		if(pWaldo->GetLocation()->X < pWaldo->GetPengyLocation()->X)
			Weapon * weapon = new Weapon(pWl, GadgetView::GadgetImage::RottenFish, Direction::Right, 0.3, 300, Character::Instance());
		else
			Weapon * weapon = new Weapon(pWl, GadgetView::GadgetImage::RottenFish, Direction::Left, 0.3, 300, Character::Instance());
		
		throws = 0;
		throwsInterval = RandomIntBetween(1000, 1200);
	}
	else
		throws++;
}

int WaldoAttack::RandomIntBetween(int a, int b)
{
	srand((unsigned)time(0));
	int random_integer;
	int lowest = a, highest = b;
	int range =(highest-lowest) + 1; 
	return lowest + int(range*rand()/(RAND_MAX + 1.0));
}