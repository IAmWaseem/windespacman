#pragma once
#include "Weapon.h"
#include "EnemyFactory.h"

Weapon::Weapon(Location * pLocation, GadgetView::GadgetImage gadgetImage, Direction direction, float speed, int maxDistance, Character * pPengy) : Gadget(0, pLocation, gadgetImage)
{
	MessageQueue::Instance()->Attach(this);
	this->direction = direction;
	this->speed = speed;
	this->maxDistance = maxDistance;
	distanceCovered = 0;
	this->pPengy = pPengy;
	hitPengy = true;
}

Weapon::Weapon(Location * pLocation, GadgetView::GadgetImage gadgetImage, Direction direction, float speed, int maxDistance, Enemy * pEnemy) : Gadget(0, pLocation, gadgetImage)
{
	MessageQueue::Instance()->Attach(this);
	this->direction = direction;
	this->speed = speed;
	this->maxDistance = maxDistance;
	distanceCovered = 0;
	this->pEnemy = pEnemy;
	hitPengy = false;
}

Weapon::~Weapon(void)
{
	this->Remove();
	MessageQueue::Instance()->Detach(this);
}

void Weapon::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	int timeElapsed;
	switch(message)
	{
	case CM_UPDATE:
		timeElapsed = (int)wParam;
		Update(timeElapsed);
		break;
	case CM_LEVEL_LOAD:
		if(hitPengy)
			delete this;
		break;
	}
}

void Weapon::Update(int timeElapsed)
{
	int distanceTraveled = speed * timeElapsed;
	distanceCovered += distanceTraveled;
	if(distanceCovered > maxDistance)
		delete this;
	else
	{
		if(direction == Direction::Right)
			pLocation->X += distanceTraveled;
		else
			pLocation->X -= distanceTraveled;
		
		ChechkCollision();
	}
}

void Weapon::ChechkCollision()
{
	if(this == NULL)
		return;
	Location * toCheck;
 	if(hitPengy)
		toCheck = pPengy->GetLocation();
	else
		toCheck = pEnemy->GetLocation();

	if(this->LocationInGadgetX(toCheck, this->pLocation) && this->LocationInGadgetY(toCheck, this->pLocation))
	{
		if(hitPengy) {
			MessageQueue::Instance()->SendMessage(CM_CHARACTER_HIT_BY_ROTTEN_FISH, NULL, NULL);	
		}
		else {
			pEnemy->DoDamage(100);
		}
		delete this;
	}
}
