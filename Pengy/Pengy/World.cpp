#include "World.h"
#include "Menu.h"
#include "GadgetFactory.h"
#include "EnemyFactory.h"
#include "Character.h"
#include "GameOverView.h"

World* World::pInstance = NULL;

World* World::Instance(){
  if(pInstance == NULL){
    pInstance = new World();
  }
  return pInstance;
}

World::World()
{ 
	level = 1;
	menu = true;
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
			pMenuObject->Instance()->DeleteGameMenu();
		}
		else
		{
			menu = true;
			pMenuObject->Instance()->LoadGameMenu();
		}
		break;
	case CM_UPDATE:
		if(Character::Instance()->GetAmountLives() == 0)
		{
			MessageQueue::Instance()->SendMessage(CM_GAME_OVER, NULL, NULL);
			//GameOverView * gameOver = new GameOverView();
			level = 1;
		}
		break;
	case CM_GAME_RESTART:
		StartGame();
		break;
	}
	
}

void World::LoadNextLevel()
{
	if(level<3)
	{
		level++;
		GadgetFactory::Instance()->StartGame();
		pMessageQueue->Instance()->SendMessage(CM_LEVEL_LOAD, NULL, NULL);
	}
}

void World::StartGame()
{
	level = 1;	
	pMessageQueue->Instance()->SendMessage(CM_LEVEL_LOAD, NULL, NULL);
}