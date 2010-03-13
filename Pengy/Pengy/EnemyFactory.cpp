#include "EnemyFactory.h"
#include "Surface.h"
#include "Location.h"
#include "Waldo.h"
#include "Enemy.h"

EnemyFactory * EnemyFactory::pInstance = NULL;

EnemyFactory * EnemyFactory::Instance()
{
	if(pInstance == NULL)
		pInstance = new EnemyFactory();
	return pInstance;
}

EnemyFactory::EnemyFactory(void)
{
	enemies = new vector<Enemy*>();
}

EnemyFactory::~EnemyFactory(void)
{
}

void EnemyFactory::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	Enemy * enemy;
	Surface * surface;
	Location * location;
	int x;
	switch(message)
	{
	case CM_GAME_START:
		startGame();
		break;
	case CM_ENEMYFACTORY_CREATE_WALDO_PATROL:
		surface = (Surface*)wParam;
		enemy = new Waldo(surface);
		enemies->push_back(enemy);
		break;
	case CM_ENEMYFACTORY_CREATE_WALDO_WANDER:
		surface = (Surface*)wParam;
		x = lParam;
		enemy = new Waldo(surface, x);
		enemies->push_back(enemy);

		break;
	}

	vector<Enemy*>::iterator iterator = enemies->begin();
	while(iterator != enemies->end())
	{
		enemy = *iterator;
		enemy->recieveMessage(message, wParam, lParam);
		iterator++;
	}
}
void EnemyFactory::startGame()
{
	Enemy * enemy;
	vector<Enemy*>::iterator iterator = enemies->begin();
	while(iterator != enemies->end())
	{
		enemy = *iterator;
		delete enemy;
		iterator++;
	}
	enemies->clear();
}
