#pragma once
#include "Weapon.h"

Weapon::Weapon(Location * pLocation, GadgetView::GadgetImage gadgetImage, Direction direction, float speed, int maxDistance) : Gadget(0, pLocation, gadgetImage)
{
	MessageQueue::Instance()->Attach(this);
	this->direction = direction;
	this->speed = speed;
	this->maxDistance = maxDistance;
	distanceCovered = 0;
}

Weapon::~Weapon(void)
{
	MessageQueue::Instance()->Detach(this);
	delete this->pGadgetStateMachine;
	this->pGadgetView->UnRegisterToGraphics();
	delete this->pGadgetView;
}

void Weapon::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	int timeElapsed;
	switch(message)
	{
	case CM_UPDATE:
		timeElapsed = (int)wParam;
		Update(timeElapsed);
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
	}

}
