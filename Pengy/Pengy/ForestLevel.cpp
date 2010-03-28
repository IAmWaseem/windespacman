#include "ForestLevel.h"

ForestLevel::ForestLevel(void)
{
	MovingSurface * movingSurface_1 = NULL;
	MovingSurface * movingSurface_2 = NULL;
	MovingSurface * movingSurface_3 = NULL;
	MovingSurface * movingSurface_4 = NULL;
	MovingSurface * movingSurface_5 = NULL;
}

ForestLevel::~ForestLevel(void)
{
	if(movingSurface_1 != NULL)
		delete movingSurface_1;
	if(movingSurface_2 != NULL)
		delete movingSurface_2;
	if(movingSurface_3 != NULL)
		delete movingSurface_3;
	if(movingSurface_4 != NULL)
		delete movingSurface_4;
	if(movingSurface_5 != NULL)
		delete movingSurface_5;
	
}

void ForestLevel::LoadGadgets()
{

}

vector<Surface*> ForestLevel::GetSurfaces()
{
	vector<Surface*> surfaces;

	Surface * borderBottom = new Surface();
	borderBottom->xFrom = 0;
	borderBottom->xTo = 3302;
	borderBottom->yFrom = 670;
	borderBottom->yTo = 700;
	borderBottom->isSurfaceOfDeath = true;
	surfaces.push_back(borderBottom);

	Surface * borderLeft = new Surface();
	borderLeft->xFrom = 0;
	borderLeft->xTo = 8;
	borderLeft->yFrom = -100;
	borderLeft->yTo = 700;
	surfaces.push_back(borderLeft);	

	Surface * borderRight = new Surface();
	borderRight->xFrom = 3300;
	borderRight->xTo = 3310;
	borderRight->yFrom = -100;
	borderRight->yTo = 700;
	surfaces.push_back(borderRight);

	Surface * borderTop = new Surface();
	borderTop->xFrom = 0;
	borderTop->xTo = 3302;
	borderTop->yFrom = -120;
	borderTop->yTo = -100;
	surfaces.push_back(borderTop);

	Surface * landLeft = new Surface();
	landLeft->xFrom = 0;
	landLeft->xTo = 530;
	landLeft->yFrom = 576;
	landLeft->yTo = 670;
	surfaces.push_back(landLeft);

	movingSurface_1 = new MovingSurface(675, 532, 803, 500, 120, true, MovingSurfaceType::Plank);
	MessageQueue::Instance()->Attach(movingSurface_1);
	surfaces.push_back(movingSurface_1);

	movingSurface_2 = new MovingSurface(675, 275, 803, 245, 120, false, MovingSurfaceType::Plank);
	MessageQueue::Instance()->Attach(movingSurface_2);
	surfaces.push_back(movingSurface_2);

	Surface * treeTrunkLeft = new Surface();
	treeTrunkLeft->xFrom = 905;
	treeTrunkLeft->xTo = 1005;
	treeTrunkLeft->yFrom = 500;
	treeTrunkLeft->yTo = 550;
	surfaces.push_back(treeTrunkLeft);

	movingSurface_3 = new MovingSurface(910, 75, 1038, 45, 200, false, MovingSurfaceType::Plank);
	MessageQueue::Instance()->Attach(movingSurface_3);
	surfaces.push_back(movingSurface_3);

	barTop = new Surface();
	barTop->xFrom = 1162;
	barTop->xTo = 1843;
	barTop->yFrom = 147;
	barTop->yTo = 174;
	surfaces.push_back(barTop);

	movingSurface_4 = new MovingSurface(1200, 275, 1238, 245, 250, false, MovingSurfaceType::Plank);
	MessageQueue::Instance()->Attach(movingSurface_4);
	surfaces.push_back(movingSurface_4);

	movingSurface_5 = new MovingSurface(1510, 375, 1638, 345, 100, false, MovingSurfaceType::Plank);
	MessageQueue::Instance()->Attach(movingSurface_5);
	surfaces.push_back(movingSurface_5);

	Surface * treeTrunkMiddle = new Surface();
	treeTrunkMiddle->xFrom = 1805;
	treeTrunkMiddle->xTo = 1920;
	treeTrunkMiddle->yFrom = 490;
	treeTrunkMiddle->yTo = 540;
	surfaces.push_back(treeTrunkMiddle);

	Surface * treeTrunkRight = new Surface();
	treeTrunkRight->xFrom = 2250;
	treeTrunkRight->xTo = 2350;
	treeTrunkRight->yFrom = 590;
	treeTrunkRight->yTo = 740;
	surfaces.push_back(treeTrunkRight);

	landRight = new Surface();
	landRight->xFrom = 2670;
	landRight->xTo = 3300;
	landRight->yFrom = 576;
	landRight->yTo = 670;
	surfaces.push_back(landRight);

	return surfaces;
}

vector<int*> ForestLevel::GetTiles()
{
	
	vector<int*> tiles;

	//mountans and sky background
	for(int x = 0; x <= 32; x++)
	{
		int tileX = x;
		for(int y = 0; y <= 11;y++)
		{
			int tileY = y + 15;
			int *tempTile = new int[6];
			tempTile[0] = x;
			tempTile[1] = y;
			tempTile[2] = tileX;
			tempTile[3] = tileY;
			tempTile[4] = 0;
			tempTile[5] = 3;
			tiles.push_back(tempTile);
		}
	}

	//second background layer
	for(int x = 0; x <= 63; x++)
	{
		int tileX = x;
		for(int y = 5; y <= 11;y++)
		{
			int tileY = y + 21;
			int *tempTile = new int[6];
			tempTile[0] = x;
			tempTile[1] = y;
			tempTile[2] = tileX;
			tempTile[3] = tileY;
			tempTile[4] = 1;
			tempTile[5] = 2;
			tiles.push_back(tempTile);
		}
	}

	//third background layer
	for(int x = 0; x <= 63; x++)
	{
		int tileX = x;
		for(int y = 5; y <= 11;y++)
		{
			int tileY = y + 27;
			int *tempTile = new int[6];
			tempTile[0] = x;
			tempTile[1] = y;
			tempTile[2] = tileX;
			tempTile[3] = tileY;
			tempTile[4] = 1;
			tempTile[5] = 1;
			tiles.push_back(tempTile);
		}
	}
	
	//first groudn part
	for(int x = 0; x <= 7; x++)
	{
		int tileX = 38;
		int tileY = 15;
		int *tempTile = new int[6];
		tempTile[0] = x;
		tempTile[1] = 9;
		tempTile[2] = tileX;
		tempTile[3] = tileY;
		tempTile[4] = 0;
		tempTile[5] = 0;
		tiles.push_back(tempTile);

		tileX = 38;
		tileY = 16;
		tempTile = new int[6];
		tempTile[0] = x;
		tempTile[1] = 10;
		tempTile[2] = tileX;
		tempTile[3] = tileY;
		tempTile[4] = 0;
		tempTile[5] = 0;
		tiles.push_back(tempTile);
	}

	for(int x = 8; x <= 9; x++)
	{
		int tileX = 24 + x;
		int tileY = 15;
		int *tempTile = new int[6];
		tempTile[0] = x;
		tempTile[1] = 9;
		tempTile[2] = tileX;
		tempTile[3] = tileY;
		tempTile[4] = 1;
		tempTile[5] = 0;
		tiles.push_back(tempTile);

		tileY = 16;
		tempTile = new int[6];
		tempTile[0] = x;
		tempTile[1] = 10;
		tempTile[2] = tileX;
		tempTile[3] = tileY;
		tempTile[4] = 1;
		tempTile[5] = 0;
		tiles.push_back(tempTile);
	}

	//tree trunks
	for(int x = 14; x <= 16; x++)
	{
		int tileX = x + 18;
		for(int y = 7; y <= 10;y++)
		{
			int tileY = y + 11;
			int *tempTile = new int[6];
			tempTile[0] = x;
			tempTile[1] = y;
			tempTile[2] = tileX;
			tempTile[3] = tileY;
			tempTile[4] = 1;
			tempTile[5] = 0;
			tiles.push_back(tempTile);
		}
	}
	
	for(int x = 28; x <= 29; x++)
	{
		int tileX = x + 7;
		for(int y = 7; y <= 10;y++)
		{
			int tileY = y + 11;
			int *tempTile = new int[6];
			tempTile[0] = x;
			tempTile[1] = y;
			tempTile[2] = tileX;
			tempTile[3] = tileY;
			tempTile[4] = 1;
			tempTile[5] = 0;
			tiles.push_back(tempTile);
		}
	}

	for(int x = 35; x <= 36; x++)
	{
		int tileX = x + 2;
		for(int y = 9; y <= 10;y++)
		{
			int tileY = y + 9;
			int *tempTile = new int[6];
			tempTile[0] = x;
			tempTile[1] = y;
			tempTile[2] = tileX;
			tempTile[3] = tileY;
			tempTile[4] = 1;
			tempTile[5] = 0;
			tiles.push_back(tempTile);
		}
	}

	//second ground part
	for(int x = 38; x <= 41; x++)
	{
		int tileX = x - 4;
		int tileY = 15;
		int *tempTile = new int[6];
		tempTile[0] = x;
		tempTile[1] = 9;
		tempTile[2] = tileX;
		tempTile[3] = tileY;
		tempTile[4] = 1;
		tempTile[5] = 0;
		tiles.push_back(tempTile);

		tileY = 16;
		tempTile = new int[6];
		tempTile[0] = x;
		tempTile[1] = 10;
		tempTile[2] = tileX;
		tempTile[3] = tileY;
		tempTile[4] = 0;
		tempTile[5] = 0;
		tiles.push_back(tempTile);
	}

	for(int x = 42; x <= 56; x++)
	{
		int tileX = 38;
		int tileY = 15;
		int *tempTile = new int[6];
		tempTile[0] = x;
		tempTile[1] = 9;
		tempTile[2] = tileX;
		tempTile[3] = tileY;
		tempTile[4] = 0;
		tempTile[5] = 0;
		tiles.push_back(tempTile);

		tileX = 38;
		tileY = 16;
		tempTile = new int[6];
		tempTile[0] = x;
		tempTile[1] = 10;
		tempTile[2] = tileX;
		tempTile[3] = tileY;
		tempTile[4] = 0;
		tempTile[5] = 0;
		tiles.push_back(tempTile);
	}

	for(int x = 18; x <= 28; x++)
	{
		int tileX = x + 14;
		int tileY = 17;
		int *tempTile = new int[6];
		tempTile[0] = x;
		tempTile[1] = 2;
		tempTile[2] = tileX;
		tempTile[3] = tileY;
		tempTile[4] = 1;
		tempTile[5] = 0;
		tiles.push_back(tempTile);
	}

	return SortTiles(tiles);
}

void ForestLevel::LoadEnemies()
{
	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_PATROL, (int)((Surface*)movingSurface_1), NULL);
	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_PATROL, (int)((Surface*)movingSurface_3), NULL);
	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_PATROL, (int)((Surface*)movingSurface_4), NULL);
	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_PATROL, (int)((Surface*)movingSurface_5), NULL);

	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_SUPERWALDO_WANDER, (int)barTop, barTop->xFrom + 40 );
	//MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)barTop, barTop->xTo - 40 );

	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)landRight, landRight->xFrom + 40 );
	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)landRight, ((landRight->xTo + landRight->xFrom) / 2));
	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)landRight, landRight->xTo - 40 );
}

