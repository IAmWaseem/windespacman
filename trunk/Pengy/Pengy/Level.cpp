#include "Level.h"
#include "Location.h"

Level* Level::pInstance = NULL;

Level* Level::Inst(){
  if(pInstance == NULL){
    pInstance = new Level();
  }
  return pInstance;
}

Level::Level(){ 
	surfaces = new vector<Surface*>();

	Surface * surface1 = new Surface();
	surface1->xFrom = 0;
	surface1->yFrom = 483;
	surface1->xTo = 367;
	surface1->yTo = 483;

	Surface * surface2 = new Surface();
	surface2->xFrom = 586;
	surface2->yFrom = 483;
	surface2->xTo = 800;
	surface2->yTo = 483;

	surfaces->push_back(surface1);
	surfaces->push_back(surface2);
}

Level::~Level(){
  if(pInstance != 0)delete pInstance;
}

void Level::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
{
	Location * fromLocation;
	Location * toLocation;
	bool isFalling;
	vector<Surface*>::iterator iterator;

	switch (message) 
	{
	case CM_KEY:
		break;
	case CM_LEVEL_START:
		LoadLevel(1);
		break;
	case CM_CHARACTER_MOVE_X_FROM_TO:
		fromLocation = (Location*)wParam;
		toLocation = (Location*)lParam;
		iterator = surfaces->begin();
		while(iterator != surfaces->end())
		{
			iterator++;
		}
		break;

	case CM_CHARACTER_FALL_Y_FROM_TO:
		fromLocation = (Location*)wParam;
		toLocation = (Location*)lParam;
		isFalling = true;
		iterator = surfaces->begin();
		while(iterator != surfaces->end())
		{
			Surface * surface = *iterator;
			if(surface->yFrom - (toLocation->Y + toLocation->height) < 1)
			{
				if(surface->xFrom <= toLocation->X && surface->xTo >= (toLocation->X + toLocation->width))
				{
					isFalling = false;
				}
				if(surface->xFrom >= toLocation->X && surface->xTo <= (toLocation->X + toLocation->width))
				{
					isFalling = false;
				}
				if(surface->xFrom <= toLocation->X && surface->xTo <= (toLocation->X + toLocation->width) && surface->xTo > toLocation->X)
				{
					isFalling = false;
				}
				if(surface->xFrom >= toLocation->X && surface->xFrom <= (toLocation->X + toLocation->width) && surface->xTo >= (toLocation->X + toLocation->width))
				{
					isFalling = false;
				}
			}
			iterator++;
		}
		if(isFalling)
		{
			MessageQueue::Inst()->sendMessage(CM_CHARACTER_IS_FALLING, NULL, NULL);
		}
		else
		{
			MessageQueue::Inst()->sendMessage(CM_CHARACTER_IS_STANDING, NULL, NULL);
		}
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
		path = "res/Summer.bmp";
		 data = GetLevel1Array();
		break;
	case 2:
		path = "res/Summer.bmp";
		data = GetLevel1Array();
		break;
	case 3:
		path = "res/Summer.bmp";
		data = GetLevel1Array();
		break;
	}

	vector<int*>::iterator iterator = data.begin();
	while(iterator!=data.end())
	{
		int* dataRow = *iterator;

		if(dataRow[4] == 1)
			myTiles.push_back(Tile(dataRow[0],dataRow[1],dataRow[2],dataRow[3],true));
		else
			myTiles.push_back(Tile(dataRow[0],dataRow[1],dataRow[2],dataRow[3],false));

		iterator++;
	}

	levelView.SetTiles(myTiles, path);
}

vector<int*> Level::GetLevel1Array()
{
	vector<int*> data;
	
	// bottom data
	for(int i = 0; i < 8; i++)
	{
		int* temp = new int[5]; temp[0] = i; temp[1] = 10; temp[2] = 0; temp[3] = 0; temp[4] = 0;
		data.push_back(temp);
	}
	// bottom data
	for(int i = 0; i < 8; i++)
	{
		int* temp = new int[5]; temp[0] = i; temp[1] = 11; temp[2] = 0; temp[3] = 1; temp[4] = 0;
		data.push_back(temp);
	}


	// water part
	int* water1 = new int[5] ; water1[0] = 8; water1[1] = 10; water1[2] = 1; water1[3] = 0; water1[4] = 0;
	int* water2 = new int[5] ; water2[0] = 8; water2[1] = 11; water2[2] = 1; water2[3] = 1; water2[4] = 0;
	int* water3 = new int[5] ; water3[0] = 9; water3[1] = 10; water3[2] = 2; water3[3] = 0; water3[4] = 0;
	int* water4 = new int[5] ; water4[0] = 9; water4[1] = 11; water4[2] = 2; water4[3] = 1; water4[4] = 0;
	int* water5 = new int[5] ; water5[0] = 10; water5[1] = 10; water5[2] = 4; water5[3] = 0; water5[4] = 0;
	int* water6 = new int[5] ; water6[0] = 10; water6[1] = 11; water6[2] = 4; water6[3] = 1; water6[4] = 0;
	int* water7 = new int[5] ; water7[0] = 11; water7[1] = 10; water7[2] = 5; water7[3] = 0; water7[4] = 0;
	int* water8 = new int[5] ; water8[0] = 11; water8[1] = 11; water8[2] = 5; water8[3] = 1; water8[4] = 0;
	data.push_back(water1); data.push_back(water2); data.push_back(water3); data.push_back(water4);
	data.push_back(water5); data.push_back(water6); data.push_back(water7); data.push_back(water8);

	// bottom data
	for(int i = 12; i < 20; i++)
	{
		int* temp = new int[5]; temp[0] = i; temp[1] = 10; temp[2] = 0; temp[3] = 0; temp[4] = 0;
		data.push_back(temp);
	}
	// bottom data
	for(int i = 12; i < 20; i++)
	{
		int* temp = new int[5]; temp[0] = i; temp[1] = 11; temp[2] = 0; temp[3] = 1; temp[4] = 0;
		data.push_back(temp);
	}

	return data;
}
