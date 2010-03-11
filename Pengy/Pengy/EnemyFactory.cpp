#include "EnemyFactory.h"
#include "Surface.h"
#include "Location.h"
#include "Waldo.h"

EnemyFactory * EnemyFactory::pInstance = NULL;

EnemyFactory * EnemyFactory::Instance()
{
	if(pInstance == NULL)
		pInstance = new EnemyFactory();
	return pInstance;
}

EnemyFactory::EnemyFactory(void)
{
	enemies = new vector<Waldo*>();
}

EnemyFactory::~EnemyFactory(void)
{
}

void EnemyFactory::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	Waldo * waldo;
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
		waldo = new Waldo(surface);
		enemies->push_back(waldo);
		break;
	case CM_ENEMYFACTORY_CREATE_WALDO_WANDER:
		surface = (Surface*)wParam;
		x = lParam;
		waldo = new Waldo(surface, x);
		enemies->push_back(waldo);

		break;
	}

	vector<Waldo*>::iterator iterator = enemies->begin();
	while(iterator != enemies->end())
	{
		waldo = *iterator;
		waldo->recieveMessage(message, wParam, lParam);
		iterator++;
	}
}
void EnemyFactory::startGame()
{
	Waldo * waldo;
	vector<Waldo*>::iterator iterator = enemies->begin();
	while(iterator != enemies->end())
	{
		waldo = *iterator;
		waldo->~Waldo();
		iterator++;
	}
	enemies->clear();
}
