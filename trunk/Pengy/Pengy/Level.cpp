#include "Level.h"

Level* Level::pInstance = NULL;

Level* Level::Inst(){
  if(pInstance == NULL){
    pInstance = new Level();
  }
  return pInstance;
}

Level::Level(){ 
}

Level::~Level(){
  if(pInstance != 0)delete pInstance;
}

void Level::recieveMessage(UINT message) 
{
	switch (message) 
	{
	case CM_KEY:
		break;
	case CM_LEVEL_START:
		LoadLevel(1);
		break;
	}
}

void Level::LoadLevel(int level)
{
	int* myInt;
	vector<int*> myTiles;

	switch(level)
	{
	case 1:
		myInt = 0;
		myTiles.push_back(myInt);
		levelView.SetTiles(myTiles);
		break;
	case 2:
		break;
	case 3:
		break;
	}
}
