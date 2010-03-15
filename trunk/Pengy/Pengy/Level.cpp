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
	//default level 1
	surfaces = beach.GetSurfaces();
	SetLevelLength();
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
	Location * pL1 = new Location();
	Location * pL2 = new Location();
	Location * pL3 = new Location();
	Location * pL4 = new Location();
	Location * pL5 = new Location();
	Location * pL6 = new Location();
	Location * pL7 = new Location();
	Location * pL8 = new Location();
	Location * pL9 = new Location();

	pL1->X = 400;
	pL1->Y = 300;

	pL2->X = 200;
	pL2->Y = 300;

	pL3->X = 300;
	pL3->Y = 300;

	pL4->X = 600;
	pL4->Y = 100;

	pL5->X = 900;
	pL5->Y = 100;

	pL6->X = 1000;
	pL6->Y = 300;

	pL7->X = 760;
	pL7->Y = 300;

	pL8->X = 1050;
	pL8->Y = 300;

	pL9->X = 500;
	pL9->Y = 900;

	switch (message) 
	{
	case CM_KEY:
		break;
	case CM_LEVEL_LOAD:
		LoadLevel(pWorld->Instance()->level);
		MessageQueue::Instance()->SendMessage(CM_LEVEL_LENGTH, levelLength, NULL);
		MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_PIRANHA, (int)pL1, NULL);
		MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pL2, NULL);
		MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pL3, NULL);
		MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pL4, NULL);
		MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pL5, NULL);
		MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_PIRANHA, (int)pL6, NULL);
		MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_PIRANHA, (int)pL7, NULL);
		MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_PIRANHA, (int)pL8, NULL);
		MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_PIRANHA, (int)pL9, NULL);
		//MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)surfaces.at(5), ((surfaces.at(5)->xFrom + surfaces.at(5)->xTo) / 2) + 10 );
		MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_PATROL, (int)surfaces.at(9), NULL);
		MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_PATROL, (int)surfaces.at(11), NULL);
		MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_PATROL, (int)surfaces.at(10), NULL);
		MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_PATROL, (int)surfaces.at(13), NULL);
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
		SetLevelLength();
		break;
	//case 2:
	//	path = "res/Summer.bmp";
	//	data = GetLevel1Array();
	//	break;
	//case 3:
	//	path = "res/Summer.bmp";
	//	data = GetLevel1Array();
	//	break;
	default:
		//level1
		path = "res/tilemap.bmp";
		data = beach.GetTiles();
		surfaces = beach.GetSurfaces();
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