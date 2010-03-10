#include "World.h"
#include "Menu.h"

World* World::pInstance = NULL;

World* World::Inst(){
  if(pInstance == NULL){
    pInstance = new World();
  }
  return pInstance;
}

World::World()
{ 
	level = 0;
	menu = false;
}

World::~World(){
  if(pInstance != 0)delete pInstance;
}

void World::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
 {
	switch (message) 
	{
	case CM_LEVEL_START:
		LoadNextLevel();
		break;
	case CM_MENU_LOAD:
		if(menu)
		{
			menu = false;
			menuObject->Inst()->DeleteGameMenu();
		}
		else
		{
			menu = true;
			menuObject->Inst()->LoadGameMenu();
		}
		break;
	}
}

void World::LoadNextLevel()
{
	if(level<3)
	{
		level++;
		messageQueue->Inst()->sendMessage(CM_LEVEL_LOAD, NULL, NULL);
	}
}
