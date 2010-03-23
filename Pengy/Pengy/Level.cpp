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
	Location * pL1 = new Location();
	Location * pL2 = new Location();
	Location * pL3 = new Location();
	Location * pL4 = new Location();
	Location * pL5 = new Location();
	Location * pL6 = new Location();
	Location * pL7 = new Location();
	Location * pL8 = new Location();
	Location * pL9 = new Location();

	// goldfish
	pL2->X = 420;
	pL2->Y = 495;

	pL3->X = 544;
	pL3->Y = 495;

	pL4->X = 1185;
	pL4->Y = 90;

	pL5->X = 1378;
	pL5->Y = 285;
	// end of gf

	// piranah
	pL1->X = 862;
	pL1->Y = 300;

	pL6->X = 995;
	pL6->Y = 240;

	pL7->X = 1364;
	pL7->Y = 110;

	pL8->X = 1492;
	pL8->Y = 110;

	pL9->X = 1700;
	pL9->Y = 300;
	// end of piranha

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
		//MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)surfaces.at(6), (surfaces.at(6)->xFrom + surfaces.at(6)->xTo) / 2 + 10 );
		//MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)surfaces.at(25), (surfaces.at(25)->xFrom + surfaces.at(25)->xTo) / 4 + 10 );
		//MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)surfaces.at(6), (surfaces.at(6)->xTo) - 10 );
		//MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)surfaces.at(6), (surfaces.at(6)->xFrom) + 10 );
		//MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_PATROL, (int)surfaces.at(14), NULL);
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
	SnowLevel snowLevel;
	switch(level)
	{
	case 1:
		path = "res/tilemap.bmp";
		data = snowLevel.GetTiles();
		surfaces = snowLevel.GetSurfaces();
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