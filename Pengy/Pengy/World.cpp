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

void World::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
 {
	switch (message) 
	{
	case CM_LEVEL_START:
		LoadNextLevel();
		break;
	case CM_GAME_START:
		StartGame();
		break;
	case CM_MENU_LOAD:
		if(menu)
		{
			menu = false;
			menuObject->Instance()->DeleteGameMenu();
		}
		else
		{
			menu = true;
			menuObject->Instance()->LoadGameMenu();
		}
		break;
	}
}

void World::LoadNextLevel()
{
	if(level<3)
	{
		level++;
		messageQueue->Instance()->SendMessage(CM_LEVEL_LOAD, NULL, NULL);
	}
}

void World::StartGame()
{
	level = 1;
	messageQueue->Instance()->SendMessage(CM_LEVEL_LOAD, NULL, NULL);
}