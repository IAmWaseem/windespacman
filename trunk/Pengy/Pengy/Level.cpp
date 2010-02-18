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

void Level::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
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
	vector<Tile*> myTiles;
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
			myTiles.push_back(&Tile(dataRow[0],dataRow[1],dataRow[2],dataRow[3],true));
		else
			myTiles.push_back(&Tile(dataRow[0],dataRow[1],dataRow[2],dataRow[3],false));

		iterator++;
	}

	levelView.SetTiles(myTiles, path);
}

vector<int*> Level::GetLevel1Array()
{
	vector<int*> data;
	
	// level data
	int b[5]= { 0, 0, 0, 0, 1 }; data.push_back(b);

	return data;
}
