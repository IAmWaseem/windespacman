#include "EnemyFactory.h"
#include "Surface.h"
#include "Location.h"
#include "Waldo.h"
#include "Enemy.h"
#include "BeachBall.h"
//#include "MisterFrost.h"

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
	isPaused = false;
}

EnemyFactory::~EnemyFactory(void)
{
}

void EnemyFactory::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	if(message == CM_UNPAUSE)
		isPaused = false;
	if(isPaused)
		return;

	bool stopSending = false;
	Enemy * pEnemy;
	Surface * pSurface;
	Location * pLocation;
	int x;
	switch(message)
	{
	case CM_GAME_START:
		//StartGame();
		break;
	case CM_ENEMYFACTORY_CREATE_WALDO_PATROL:
		pSurface = (Surface*)wParam;
		pEnemy = new Waldo(pSurface);
		pEnemies->push_back(pEnemy);
		break;
	case CM_ENEMYFACTORY_CREATE_BEACHBALL:
		pSurface = (Surface*)wParam;
		x = lParam;
		pEnemy = new BeachBall(pSurface);
		pEnemies->push_back(pEnemy);
		break;
	case CM_ENEMYFACTORY_CREATE_MISTERFROST:
		pSurface = (Surface*)wParam;
		x = lParam;
		//pEnemy = new MisterFrost(pSurface);
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
	case CM_ENEMYFACTORY_CLEAR:
		StartGame();
		break;
	case CM_UPDATE:
		CleanUp();
		break;
	case CM_PAUSE:
		isPaused = true;
		break;
	}
	
	vector<Enemy*>::iterator iterator = pEnemies->begin();
	while(iterator != pEnemies->end())
	{
		pEnemy = *iterator;
		pEnemy->ReceiveMessage(message, wParam, lParam);
		iterator++;
	}
}
void EnemyFactory::StartGame()
{
	Enemy * pEnemy;
	for(int n=0; n<pEnemies->size(); n++)
	{
		pEnemy = pEnemies->at(n);
		if(!pEnemy->IsDeleted())
			pEnemy->Delete();
	}
}

vector<Enemy*> * EnemyFactory::GetEnemies()
{
	return pEnemies;
}

void EnemyFactory::CleanUp()
{
	vector<Enemy*> * newEnemies = new vector<Enemy*>();
	Enemy * pEnemy;
	for(int n=0; n<pEnemies->size(); n++)
	{
		pEnemy = pEnemies->at(n);
		if(pEnemy->IsDeleted())
		{
			delete pEnemy;
			pEnemy = NULL;
		}
		else
		{
			newEnemies->push_back(pEnemy);
		}
	}
	if(pEnemies->size() > newEnemies->size())
	{
		int x = 8;
	}
	pEnemies->clear();
	pEnemies = newEnemies;
}
