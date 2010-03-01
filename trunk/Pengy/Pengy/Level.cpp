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
	surfaces = new vector<Surface>();

	Surface borderBottom;
	borderBottom.xFrom = 0;
	borderBottom.xTo = 1200;
	borderBottom.yFrom = 568;
	borderBottom.yTo = 600;
	surfaces->push_back(borderBottom);
	
	Surface borderLeft;
	borderLeft.xFrom = 0;
	borderLeft.xTo = 8;
	borderLeft.yFrom = 0;
	borderLeft.yTo = 600;
	surfaces->push_back(borderLeft);	

	Surface borderRight;
	borderRight.xFrom = 1181;
	borderRight.xTo = 1189;
	borderRight.yFrom = 0;
	borderRight.yTo = 600;
	surfaces->push_back(borderRight);

	Surface borderTop;
	borderTop.xFrom = 0;
	borderTop.xTo = 1200;
	borderTop.yFrom = 0;
	borderTop.yTo = 8;
	surfaces->push_back(borderTop);

	Surface surface1;
	surface1.xFrom = 0;
	surface1.xTo = 320;
	surface1.yFrom = 448;
	surface1.yTo = 600;
	surfaces->push_back(surface1);

	Surface surface2;
	surface2.xFrom = 576;
	surface2.xTo = 1200;
	surface2.yFrom = 448;
	surface2.yTo = 600;
	surfaces->push_back(surface2);

	
	



	SetLevelLength();
}

void Level::SetLevelLength()
{
	int maxX = 0;
	vector<Surface>::iterator iterator = surfaces->begin();
	while(iterator != surfaces->end())
	{
		Surface surface = *iterator;
		if(maxX < surface.xTo)
		{
			maxX = surface.xTo;
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
	Location * fromLocation;
	Location * toLocation;
	float fromLocationY;
	float toLocationY;
	bool isFalling;
	bool hitHead;
	Surface onSurface;
	vector<Surface>::iterator iterator;

	switch (message) 
	{
	case CM_KEY:
		break;
	case CM_LEVEL_START:
		LoadLevel(1);
		MessageQueue::Inst()->sendMessage(CM_LEVEL_LENGTH, levelLength, NULL);
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
		fromLocationY = fromLocation->Y + fromLocation->height;
		toLocationY = toLocation->Y + toLocation->height;
		
		if(toLocationY > fromLocationY || toLocationY == fromLocationY)
		{
			isFalling = true;
			iterator = surfaces->begin();
			while(iterator != surfaces->end())
			{
				Surface surface = *iterator;
				
				if((surface.yFrom <= toLocationY && surface.yFrom >= fromLocationY) || (toLocationY > fromLocationY && surface.yFrom < toLocationY) )
				{
					if(surface.xFrom <= toLocation->X && surface.xTo >= (toLocation->X + toLocation->width))
					{
						isFalling = false;
						onSurface = surface;
					}
					if(surface.xFrom >= toLocation->X && surface.xTo <= (toLocation->X + toLocation->width))
					{
						isFalling = false;
						onSurface = surface;
					}
					if(surface.xFrom <= toLocation->X && surface.xTo <= (toLocation->X + toLocation->width) && surface.xTo > toLocation->X)
					{
						isFalling = false;
						onSurface = surface;
					}
					if(surface.xFrom >= toLocation->X && surface.xFrom <= (toLocation->X + toLocation->width) && surface.xTo >= (toLocation->X + toLocation->width))
					{
						isFalling = false;
						onSurface = surface;
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
				MessageQueue::Inst()->sendMessage(CM_CHARACTER_IS_STANDING, (int)&onSurface, NULL);
			}
		}
		else
		{
			hitHead = false;
			iterator = surfaces->begin();
			while(iterator != surfaces->end())
			{

			}
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
		path = "res/tilemap.bmp";
		data = GetLevel1Tiles();
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
		path = "res/tilemap.bmp";
		data = GetLevel1Tiles();
		break;
	}

	vector<int*>::iterator iterator = data.begin();
	while(iterator!=data.end())
	{
		int* dataRow = *iterator;

		if(dataRow[4] == 1)
			myTiles.push_back(Tile(dataRow[0], dataRow[1], dataRow[2], dataRow[3], true));
		else
			myTiles.push_back(Tile(dataRow[0], dataRow[1], dataRow[2], dataRow[3], false));

		iterator++;
	}

	levelView.SetSurface(surfaces);
	levelView.SetTiles(myTiles, path);
}

vector<int*> Level::GetLevel1Tiles()
{
	vector<int*> data;

#pragma region bottom ground
	// bottom data
	for(int i = 0; i < 5; i++)
	{
		int* temp = new int[5]; temp[0] = i; temp[1] = 7; temp[2] = 0; temp[3] = 7; temp[4] = 0;
		data.push_back(temp);
	}
	// bottom data
	for(int i = 0; i < 5; i++)
	{
		int* temp = new int[5]; temp[0] = i; temp[1] = 8; temp[2] = 0; temp[3] = 8; temp[4] = 0;
		data.push_back(temp);
	}

	// bottom data
	for(int i = 9; i < 20; i++)
	{
		int* temp = new int[5]; temp[0] = i; temp[1] = 7; temp[2] = 0; temp[3] = 7; temp[4] = 0;
		data.push_back(temp);
	}
	// bottom data
	for(int i = 9; i < 20; i++)
	{
		int* temp = new int[5]; temp[0] = i; temp[1] = 8; temp[2] = 0; temp[3] = 8; temp[4] = 0;
		data.push_back(temp);
	}
#pragma endregion here is the creation of the ground tiles

#pragma region waterpart

	// water part
	int* water1 = new int[5] ; water1[0] = 5; water1[1] = 7; water1[2] = 1; water1[3] = 7; water1[4] = 0;
	int* water2 = new int[5] ; water2[0] = 5; water2[1] = 8; water2[2] = 1; water2[3] = 8; water2[4] = 0;
	int* water3 = new int[5] ; water3[0] = 6; water3[1] = 7; water3[2] = 2; water3[3] = 7; water3[4] = 0;
	int* water4 = new int[5] ; water4[0] = 6; water4[1] = 8; water4[2] = 2; water4[3] = 8; water4[4] = 0;
	int* water5 = new int[5] ; water5[0] = 7; water5[1] = 7; water5[2] = 3; water5[3] = 7; water5[4] = 0;
	int* water6 = new int[5] ; water6[0] = 7; water6[1] = 8; water6[2] = 3; water6[3] = 8; water6[4] = 0;
	int* water7 = new int[5] ; water7[0] = 8; water7[1] = 7; water7[2] = 4; water7[3] = 7; water7[4] = 0;
	int* water8 = new int[5] ; water8[0] = 8; water8[1] = 8; water8[2] = 4; water8[3] = 8; water8[4] = 0;
	data.push_back(water1); data.push_back(water2); data.push_back(water3); data.push_back(water4);
	data.push_back(water5); data.push_back(water6); data.push_back(water7); data.push_back(water8);

#pragma endregion here is the creation of the water tiles
//
//#pragma region tree
//
//
//
//	
//	int* tree1 = new int[5]; tree1[0] = 3; tree1[1] = 9; tree1[2] = 0; tree1[3] = 2; tree1[4] = 0;
//	int* tree2 = new int[5]; tree2[0] = 3; tree2[1] = 8; tree2[2] = 1; tree2[3] = 2; tree2[4] = 0;	
//	int* tree3 = new int[5]; tree3[0] = 3; tree3[1] = 7; tree3[2] = 2; tree3[3] = 2; tree3[4] = 0;
//	int* tree4 = new int[5]; tree4[0] = 3; tree4[1] = 6; tree4[2] = 3; tree4[3] = 2; tree4[4] = 0;
//	int* tree5 = new int[5]; tree5[0] = 3; tree5[1] = 5; tree5[2] = 4; tree5[3] = 2; tree5[4] = 0;
//	int* tree6 = new int[5]; tree6[0] = 3; tree6[1] = 4; tree6[2] = 1; tree6[3] = 3; tree6[4] = 0;
//
//	int* tree7 = new int[5]; tree7[0] = 2; tree7[1] = 5; tree7[2] = 5; tree7[3] = 2; tree7[4] = 0;
//	int* tree8 = new int[5]; tree8[0] = 0; tree8[1] = 9; tree8[2] = 0; tree8[3] = 2; tree8[4] = 0;
//	int* tree9 = new int[5]; tree9[0] = 0; tree9[1] = 9; tree9[2] = 0; tree9[3] = 2; tree9[4] = 0;
//	int* tree10 = new int[5]; tree10[0] = 0; tree10[1] = 9; tree10[2] = 0; tree10[3] = 2; tree10[4] = 0;
//	int* tree11 = new int[5]; tree11[0] = 0; tree11[1] = 9; tree11[2] = 0; tree11[3] = 2; tree11[4] = 0;
//	int* tree12 = new int[5]; tree12[0] = 0; tree12[1] = 9; tree12[2] = 0; tree12[3] = 2; tree12[4] = 0;
//	int* tree13 = new int[5]; tree13[0] = 0; tree13[1] = 9; tree13[2] = 0; tree13[3] = 2; tree13[4] = 0;
//	int* tree14 = new int[5]; tree14[0] = 0; tree14[1] = 9; tree14[2] = 0; tree14[3] = 2; tree14[4] = 0;
//	int* tree15 = new int[5]; tree15[0] = 0; tree15[1] = 9; tree15[2] = 0; tree15[3] = 2; tree15[4] = 0;
//	int* tree16 = new int[5]; tree16[0] = 0; tree16[1] = 9; tree16[2] = 0; tree16[3] = 2; tree16[4] = 0;
//	
//	data.push_back(tree1); data.push_back(tree2); data.push_back(tree3); data.push_back(tree4);
//	data.push_back(tree5); data.push_back(tree6); data.push_back(tree7); data.push_back(tree8);
//	data.push_back(tree9); data.push_back(tree10); data.push_back(tree11); data.push_back(tree12);
//	data.push_back(tree13); data.push_back(tree14); data.push_back(tree15); data.push_back(tree16);
//#pragma endregion here is the creation of the tree tiles
//

	return data;
}
