#include "EnemyFactory.h"
#include "Surface.h"
#include "Location.h"
#include "Waldo.h"
#include "Enemy.h"

EnemyFactory * EnemyFactory::pInstance = NULL;
bool EnemyFactory::SendMessagesToChildren = false;

EnemyFactory * EnemyFactory::Instance()
{
	if(pInstance == NULL)
		pInstance = new EnemyFactory();
	return pInstance;
}

EnemyFactory::EnemyFactory(void)
{
	pEnemies = new vector<Enemy*>();
}

EnemyFactory::~EnemyFactory(void)
{
}

void EnemyFactory::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	bool stopSending = false;
	Enemy * pEnemy;
	Surface * pSurface;
	Location * pLocation;
	int x;
	switch(message)
	{
	case CM_GAME_START:
		StartGame();
		break;
	case CM_ENEMYFACTORY_CREATE_WALDO_PATROL:
		pSurface = (Surface*)wParam;
		pEnemy = new Waldo(pSurface);
		pEnemies->push_back(pEnemy);
		break;
	case CM_ENEMYFACTORY_CREATE_WALDO_WANDER:
		pSurface = (Surface*)wParam;
		x = lParam;
		pEnemy = new Waldo(pSurface, x);
		pEnemies->push_back(pEnemy);
		break;
	case CM_ENEMYFACTORY_CREATE_SUPERWALDO_WANDER:
		pSurface = (Surface*)wParam;
		x = lParam;
		pEnemy = new Waldo(pSurface, x, true);
		pEnemies->push_back(pEnemy);
		break;
	case CM_LEVEL_END:
		EnemyFactory::SendMessagesToChildren = false;
		break;
	case CM_LEVEL_BEGIN:
		EnemyFactory::SendMessagesToChildren = true;
	}
	
	if(EnemyFactory::SendMessagesToChildren)
	{
		vector<Enemy*>::iterator iterator = pEnemies->begin();
		while(iterator != pEnemies->end())
		{
			pEnemy = *iterator;
			pEnemy->ReceiveMessage(message, wParam, lParam);
			if(!EnemyFactory::SendMessagesToChildren)
				return;
			iterator++;
		}
	}
}
void EnemyFactory::StartGame()
{
	Enemy * pEnemy;
	vector<Enemy*>::iterator iterator = pEnemies->begin();
	while(iterator != pEnemies->end())
	{
		pEnemy = *iterator;
		delete pEnemy;
		iterator++;
	}
	pEnemies->clear();
}
