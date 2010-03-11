#include "Level.h"
#include "Location.h"
#include "Math.h"
#include "Waldo.h"

Level* Level::pInstance = NULL;

Level* Level::Inst(){
  if(pInstance == NULL){
    pInstance = new Level();
  }
  return pInstance;
}

Level::Level()
{ 
	//default level 1
	surfaces = beach.getSurfaces();
	SetLevelLength();
}

void Level::SetLevelLength()
{
	int maxX = 0;
	vector<Surface*>::iterator iterator = surfaces.begin();
	while(iterator != surfaces.end())
	{
		Surface * surface = *iterator;
		if(maxX < surface->xTo)
		{
			maxX = surface->xTo;
		}
		iterator++;
	}
	levelLength = maxX;
}

Level::~Level(){
  if(pInstance != 0)delete pInstance;
}

void Level::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
{
	Location * gL1 = new Location();
	Location * gL2 = new Location();
	Location * gL3 = new Location();
	Location * gL4 = new Location();

	gL1->X = 400;
	gL1->Y = 300;

	gL2->X = 200;
	gL2->Y = 300;

	gL3->X = 300;
	gL3->Y = 300;

	switch (message) 
	{
	case CM_KEY:
		break;
	case CM_LEVEL_LOAD:
		LoadLevel(world->Inst()->level);
		MessageQueue::Inst()->sendMessage(CM_LEVEL_LENGTH, levelLength, NULL);
		MessageQueue::Inst()->sendMessage(CM_GADGETFACTORY_CREATE_PIRANHA, (int)gL1, NULL);
		MessageQueue::Inst()->sendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)gL2, NULL);
		MessageQueue::Inst()->sendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)gL3, NULL);
		MessageQueue::Inst()->sendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)surfaces.at(5), ((surfaces.at(5)->xFrom + surfaces.at(5)->xTo) / 2) + 10 );
		MessageQueue::Inst()->sendMessage(CM_ENEMYFACTORY_CREATE_WALDO_PATROL, (int)surfaces.at(9), NULL);
		MessageQueue::Inst()->sendMessage(CM_ENEMYFACTORY_CREATE_WALDO_PATROL, (int)surfaces.at(11), NULL);
		MessageQueue::Inst()->sendMessage(CM_ENEMYFACTORY_CREATE_WALDO_PATROL, (int)surfaces.at(10), NULL);
		MessageQueue::Inst()->sendMessage(CM_ENEMYFACTORY_CREATE_WALDO_PATROL, (int)surfaces.at(13), NULL);
		break;
	case CM_CHARACTER_MOVE_X_FROM_TO:
		if(physic_behavior.Move_X_From_To((Location*)wParam,(Location*)lParam,surfaces)==true)
			MessageQueue::Inst()->sendMessage(CM_CHARACTER_BUMPS_INTO, (int)physic_behavior.Surface_final, NULL);
		break;

	case CM_CHARACTER_FALL_Y_FROM_TO:
		if(physic_behavior.Fall_Y_From_To((Location*)wParam,(Location*)lParam,surfaces)==false)
			MessageQueue::Inst()->sendMessage(CM_CHARACTER_IS_FALLING, NULL, NULL);
		else
			MessageQueue::Inst()->sendMessage(CM_CHARACTER_IS_STANDING, (int)physic_behavior.onSurface_final_fall, NULL);
		break;

	case CM_CHARACTER_JUMP_Y_FROM_TO:
		if(physic_behavior.Jump_Y_From_To((Location*)wParam,(Location*)lParam,surfaces)==true)
			MessageQueue::Inst()->sendMessage(CM_CHARACTER_JUMPING_BUMPS_HEAD, (int)physic_behavior.onSurface_final_jump, NULL);
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
		data = beach.getTiles();
		surfaces = beach.getSurfaces();
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
		data = beach.getTiles();
		surfaces = beach.getSurfaces();
		SetLevelLength();
		break;
	}

	vector<int*>::iterator iterator = data.begin();
	while(iterator!=data.end())
	{
		

		int* dataRow = *iterator;

		int i = dataRow[5];

		if(dataRow[4] == 1)
			myTiles.push_back(Tile(dataRow[0], dataRow[1], dataRow[2], dataRow[3], true, dataRow[5]));
		else
			myTiles.push_back(Tile(dataRow[0], dataRow[1], dataRow[2], dataRow[3], false, dataRow[5]));

		iterator++;
	}

	levelView.SetSurface(&surfaces);
	levelView.SetTiles(myTiles, path);
}