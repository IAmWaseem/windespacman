#include "Enemy.h"
#include "messages.h"
#include "MessageQueue.h"
#include "View.h"
#include "EnemyFactory.h"

Enemy::Enemy(Surface * pSurface)
{
	this->pOnSurface = pSurface;
	this->pLocation = new Location();
	this->health = 100;
	this->isAlive = true;
	this->isDeleted = false;
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

void Enemy::Delete()
{
	isDeleted = true;
	if(isAlive)
	{
		pView->UnRegisterToGraphics();
		delete pView;
	}
	if(endsLevel)
		EndLevel();
}

bool Enemy::IsDeleted()
{
	return isDeleted;
}

bool Enemy::IsAlive()
{
	return isAlive;
}

void Enemy::EndLevel()
{
	EnemyFactory::SendMessagesToChildren = false;
	MessageQueue::Instance()->SendMessage(CM_LEVEL_START, NULL, NULL);
	EnemyFactory::SendMessagesToChildren = true;
}

void Enemy::DoDamage(int amount)
{
	health -= amount;
	if(health <= 0)
		this->Delete();
}

bool Enemy::EndsLevel()
{
	return endsLevel;
}

int Enemy::GetHealth()
{
	return health;
}