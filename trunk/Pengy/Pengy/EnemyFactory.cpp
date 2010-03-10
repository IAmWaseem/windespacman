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
	switch(message)
	{
	case CM_ENEMYFACTORY_CREATE_WALDO_PATROL:
		surface = (Surface*)wParam;
		waldo = new Waldo(surface);
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
