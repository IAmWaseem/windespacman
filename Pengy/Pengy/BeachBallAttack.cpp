#pragma once
#include "BeachBallAttack.h"
#include "math.h"
#include "messages.h"
#include "weapon.h"
#include "direction.h"
#include <ctime>
#include <cstdlib>
#include "character.h"

BeachBallAttack::BeachBallAttack(BeachBall * pBeachBall, BeachBallStateMachine * pBeachBallStateMachine):BeachBallState(pBeachBall, pBeachBallStateMachine)
{
	this->speed = 0.10f;
	throws = 0;
	throwsInterval = RandomIntBetween(5, 20);
}


BeachBallAttack::~BeachBallAttack(void)
{
}

void BeachBallAttack::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
{
	int timeElapsed;

	switch(message) {
		case CM_UPDATE:
		timeElapsed = wParam;
		this->Update(timeElapsed);
		break;
	}
}

void BeachBallAttack::Update(int timeElapsed) 
{
	Throw();
	pBeachBallStateMachine->Transition(pBeachBallStateMachine->pPatrol);
}

void BeachBallAttack::Throw() 
{	if(throws == throwsInterval)
	{
		Location * pWl = new Location();
		pWl->X = pBeachBall->GetLocation()->X;
		pWl->Y = pBeachBall->GetPengyLocation()->Y - (0.5 * pBeachBall->GetPengyLocation()->height);
		if(pWl->Y > pBeachBall->GetLocation()->Y)
			pWl->Y = pBeachBall->GetLocation()->Y;
		Weapon * weapon = new Weapon(pWl, GadgetView::GadgetImage::RottenFish, Direction::Left, 0.4, 500, Character::Instance());
		throws = 0;
		throwsInterval = RandomIntBetween(5, 20);
	}
	else
		throws++;
}

int BeachBallAttack::RandomIntBetween(int a, int b)
{
	srand((unsigned)time(0));
	int random_integer;
	int lowest = a, highest = b;
	int range =(highest-lowest) + 1; 
	return lowest + int(range*rand()/(RAND_MAX + 1.0));
}
