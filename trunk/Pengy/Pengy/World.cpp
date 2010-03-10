#include "World.h"

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
		//LoadMenu();
		if(menu)
			menu = false;
		else
			menu = true;
		break;
	}
}

void World::LoadNextLevel()
{
	level++;
	messageQueue->Inst()->sendMessage(CM_LEVEL_LOAD, NULL, NULL);
}
