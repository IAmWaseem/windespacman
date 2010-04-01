#pragma once
#include "MisterFrostAttack.h"
#include "math.h"
#include "messages.h"
#include "weapon.h"
#include "direction.h"
#include <ctime>
#include <cstdlib>
#include "character.h"

MisterFrostAttack::MisterFrostAttack(MisterFrost * pMisterFrost, MisterFrostStateMachine * pMisterFrostStateMachine):MisterFrostState(pMisterFrost, pMisterFrostStateMachine)
{
	this->speed = 0.10f;
	throws = 0;
	throwsInterval = RandomIntBetween(5, 20);
}


MisterFrostAttack::~MisterFrostAttack(void)
{
}

void MisterFrostAttack::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
{
	int timeElapsed;

	switch(message) {
		case CM_UPDATE:
		timeElapsed = wParam;
		this->Update(timeElapsed);
		break;
	}
}

void MisterFrostAttack::Update(int timeElapsed) 
{
	Throw();
	pMisterFrostStateMachine->Transition(pMisterFrostStateMachine->pPatrol);
}

void MisterFrostAttack::Throw() 
{	if(throws == throwsInterval)
	{
		Location * pWl = new Location();
		pWl->X = pMisterFrost->GetLocation()->X;
		pWl->Y = pMisterFrost->GetPengyLocation()->Y + (0.5 * pMisterFrost->GetPengyLocation()->height);
		if(pWl->Y > pMisterFrost->GetLocation()->Y + pMisterFrost->GetLocation()->height)
			pWl->Y = pMisterFrost->GetLocation()->Y + pMisterFrost->GetLocation()->height;
		Weapon * weapon = new Weapon(pWl, GadgetView::GadgetImage::RottenFish, Direction::Left, 0.4, 500, Character::Instance());
		throws = 0;
		throwsInterval = RandomIntBetween(5, 20);
	}
	else
		throws++;
}

int MisterFrostAttack::RandomIntBetween(int a, int b)
{
	srand((unsigned)time(0));
	int random_integer;
	int lowest = a, highest = b;
	int range =(highest-lowest) + 1; 
	return lowest + int(range*rand()/(RAND_MAX + 1.0));
}
