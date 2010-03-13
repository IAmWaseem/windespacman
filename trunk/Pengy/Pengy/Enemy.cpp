#include "Enemy.h"
#include "messages.h"
#include "MessageQueue.h"

Enemy::Enemy(Surface * pSurface)
{
	this->pOnSurface = pSurface;
	this->pLocation = new Location();
	this->health = 100;
	this->isAlive = true;
}


Enemy::~Enemy(void)
{

}

Location * Enemy::GetLocation()
{
	return this->pLocation;
}

Direction Enemy::GetDirection()
{
	return this->direction;
}

void Enemy::SetDirection(Direction direction)
{
	this->direction = direction;
}

Surface * Enemy::GetOnSurface()
{
	return this->pOnSurface;
}

Location * Enemy::GetPengyLocation()
{
	return this->pPengyLocation;
}

void Enemy::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	if(!this->isAlive)
		return;

	switch(message)
	{
	case CM_UPDATE:
		MessageQueue::Instance()->SendMessage(CM_CHARACTER_GET_LOCATION, NULL, NULL);
		break;

	case CM_CHARACTER_RETURN_LOCATION:
		this->pPengyLocation = (Location*)wParam;
		break;
	}

	if(this->isAlive)
		this->ReceiveMessageInternal(message, wParam, lParam);

}
