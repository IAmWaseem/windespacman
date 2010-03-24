#include "Level.h"
#include "Location.h"
#include "Math.h"
#include "Waldo.h"


Level* Level::pInstance = NULL;

Level* Level::Instance(){
  if(pInstance == NULL){
    pInstance = new Level();
  }
  return pInstance;
}

Level::Level()
{ 

}

void Level::SetLevelLength()
{
	int maxX = 0;
	vector<Surface*>::iterator iterator = surfaces.begin();
	while(iterator != surfaces.end())
	{
		Surface * pSurface = *iterator;
		if(maxX < pSurface->xTo)
		{
			maxX = pSurface->xTo;
		}
		iterator++;
	}
	levelLength = maxX;
}

Level::~Level(){
  if(pInstance != 0)delete pInstance;
}

void Level::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch (message) 
	{
	case CM_KEY:
		break;
	case CM_LEVEL_LOAD:
		LoadLevel(pWorld->Instance()->level);
		MessageQueue::Instance()->SendMessage(CM_LEVEL_LENGTH, levelLength, NULL);
		break;
	case CM_CHARACTER_MOVE_X_FROM_TO:
		if(physic_behavior.MoveXFromTo((Location*)wParam,(Location*)lParam,surfaces)==true)
			MessageQueue::Instance()->SendMessage(CM_CHARACTER_BUMPS_INTO, (int)physic_behavior.pSurfaceFinal, NULL);
		break;

	case CM_CHARACTER_FALL_Y_FROM_TO:
		if(physic_behavior.FallYFromTo((Location*)wParam,(Location*)lParam,surfaces)==false)
			MessageQueue::Instance()->SendMessage(CM_CHARACTER_IS_FALLING, NULL, NULL);
		else
			MessageQueue::Instance()->SendMessage(CM_CHARACTER_IS_STANDING, (int)physic_behavior.pOnSurfaceFinalFall, NULL);
		break;

	case CM_CHARACTER_JUMP_Y_FROM_TO:
		if(physic_behavior.JumpYFromTo((Location*)wParam,(Location*)lParam,surfaces)==true)
			MessageQueue::Instance()->SendMessage(CM_CHARACTER_JUMPING_BUMPS_HEAD, (int)physic_behavior.pOnSurfaceFinalJump, NULL);
		break;
	case CM_GAME_START:
		levelView.StartGame();
		MessageQueue::Instance()->SendMessage(CM_LEVEL_BEGIN, NULL, NULL);
		break;
	}
}

void Level::LoadLevel(int level)
{
	vector<Tile> myTiles;
	vector<int*> data;
	LPCSTR path = "";
	switch(level)
	{
	case 1:
		path = "res/tilemap.bmp";
		data = beach.GetTiles();
		surfaces = beach.GetSurfaces();
		beach.LoadGadgets();
		beach.LoadEnemies();
		SetLevelLength();
		break;
	case 2:
		path = "res/tilemap.bmp";
		data = snowLevel.GetTiles();
		surfaces = snowLevel.GetSurfaces();
		snowLevel.LoadGadgets();
		snowLevel.LoadEnemies();
		SetLevelLength();
		break;
	//case 3:
	//	path = "res/Summer.bmp";
	//	data = GetLevel1Array();
	//	break;
	default:
		//level1
		path = "res/tilemap.bmp";
		data = beach.GetTiles();
		surfaces = beach.GetSurfaces();
		beach.LoadGadgets();
		beach.LoadEnemies();
		SetLevelLength();
		break;
	}

	vector<int*>::iterator iterator = data.begin();
	while(iterator!=data.end())
	{
		int* dataRow = *iterator;
		if(dataRow[4] == 1)
			myTiles.push_back(Tile(dataRow[0], dataRow[1], dataRow[2], dataRow[3], true, dataRow[5]));
		else
			myTiles.push_back(Tile(dataRow[0], dataRow[1], dataRow[2], dataRow[3], false, dataRow[5]));

		iterator++;
	}

	levelView.SetSurface(&surfaces);
	levelView.SetTiles(myTiles, path);
}