#include "ForestLevel.h"
#include "Location.h"

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
	Location * pL1 = new Location();
	Location * pL2 = new Location();
	Location * pL3 = new Location();
	Location * pL4 = new Location();
	Location * pL5 = new Location();
	Location * pL6 = new Location();
	Location * pL7 = new Location();
	Location * pL8 = new Location();
	Location * pL9 = new Location();
	Location * pL10 = new Location();
	Location * pL11 = new Location();
	Location * pL12 = new Location();
	Location * pL13 = new Location();
	Location * pL14 = new Location();
	Location * pL15 = new Location();
	Location * pL16 = new Location();
	Location * pL17 = new Location();
	Location * pL18 = new Location();
	Location * pL19 = new Location();
	Location * pL20 = new Location();
	Location * pL21 = new Location();
	Location * pL22 = new Location();
	Location * pL23 = new Location();
	Location * pL24 = new Location();
	Location * pL25 = new Location();
	Location * pL26 = new Location();
	Location * pL27 = new Location();
	Location * pL28 = new Location();
	Location * pL29 = new Location();
	Location * pL30 = new Location();
	Location * pL31 = new Location();
	Location * pL32 = new Location();
	Location * pL33 = new Location();

//goldfish
	pL1->X = 500;
	pL1->Y = 500;

	pL2->X = 530;
	pL2->Y = 470;
	
	pL3->X = 560;
	pL3->Y = 440;
//piranha
	pL4->X = 600;
	pL4->Y = 440;
//goldfish
	pL5->X = 880;
	pL5->Y = 470;
//piranha
	pL6->X = 925;
	pL6->Y = 440;
//goldfish
	pL7->X = 1000;
	pL7->Y = 470;
//rottenfish
	pL8->X = 940;
	pL8->Y = 470;
//goldfish
	pL9->X = 813;
	pL9->Y = 160;

	pL10->X = 640;
	pL10->Y = 220;

	pL11->X = 600;
	pL11->Y = 180;

	pL12->X = 560;
	pL12->Y = 140;
//piranha
	pL13->X = 450;
	pL13->Y = 180;
//goldfish
	pL14->X = 850;
	pL14->Y = 100;

	pL15->X = 1100;
	pL15->Y = 40;

	pL16->X = 1150;
	pL16->Y = 20;
//goldfish
	pL17->X = 1262;
	pL17->Y = 20;
	
	pL18->X = 1700;
	pL18->Y = 20;

	pL19->X = 1780;
	pL19->Y = 465;
//rottenfish
	pL20->X = 1845;
	pL20->Y = 465;
//goldfish
	pL21->X = 1910;
	pL21->Y = 465;
//piranha
	pL22->X = 1830;
	pL22->Y = 435;
//rottenfish
	pL23->X = 1480;
	pL23->Y = 120;
//goldfish
	pL24->X = 2225;
	pL24->Y = 560;

	pL25->X = 2340;
	pL25->Y = 560;
//rottenfish
	pL26->X = 2290;
	pL26->Y = 560;
//piranha
	pL27->X = 2275;
	pL27->Y = 525;
//rottenfish
	pL28->X = 1400;
	pL28->Y = 194;

	pL29->X = 1400;
	pL29->Y = 394;

	pL30->X = 1400;
	pL30->Y = 294;
//piranha
	pL31->X = 1340;
	pL31->Y = 230;

	pL33->X = 2070;
	pL33->Y = 350;
//extralife
	pL32->X = 1440;
	pL32->Y = 230;

	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pL1, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pL2, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pL3, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_PIRANHA, (int)pL4, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pL5, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_PIRANHA, (int)pL6, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pL7, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_ROTTENFISH, (int)pL8, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pL9, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pL10, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pL11, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pL12, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_PIRANHA, (int)pL13, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pL14, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pL15, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pL16, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pL17, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pL18, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pL19, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_ROTTENFISH, (int)pL20, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pL21, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_PIRANHA, (int)pL22, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_ROTTENFISH, (int)pL23, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pL24, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pL25, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_ROTTENFISH, (int)pL26, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_PIRANHA, (int)pL27, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_ROTTENFISH, (int)pL28, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_ROTTENFISH, (int)pL29, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_ROTTENFISH, (int)pL30, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_PIRANHA, (int)pL31, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_EXTRALIFE, (int)pL32, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_PIRANHA, (int)pL33, NULL);
}

vector<Surface*> ForestLevel::GetSurfaces()
{
	vector<Surface*> surfaces;

	Surface * borderBottom = new Surface();
	borderBottom->xFrom = 0;
	borderBottom->xTo = 3302;
	borderBottom->yFrom = 670;
	borderBottom->yTo = 2000;
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
			int tileY = y + 15 - 15;
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
			int tileY = y + 21 - 15;
			int *tempTile = new int[6];
			tempTile[0] = x;
			tempTile[1] = y;
			tempTile[2] = tileX;
			tempTile[3] = tileY;
			if(y == 5 || y == 6)
				tempTile[4] = 1;
			else
				tempTile[4] = 0;
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
			int tileY = y + 27 - 15;
			int *tempTile = new int[6];
			tempTile[0] = x;
			tempTile[1] = y;
			tempTile[2] = tileX;
			tempTile[3] = tileY;
			if(y == 5 || y == 6 ||  y == 7)
				tempTile[4] = 1;
			else
				tempTile[4] = 0;
			tempTile[5] = 1;
			tiles.push_back(tempTile);
		}
	}
	
	//first groudn part
	for(int x = 0; x <= 7; x++)
	{
		int tileX = 38;
		int tileY = 15 - 15;
		int *tempTile = new int[6];
		tempTile[0] = x;
		tempTile[1] = 9;
		tempTile[2] = tileX;
		tempTile[3] = tileY;
		tempTile[4] = 0;
		tempTile[5] = 0;
		tiles.push_back(tempTile);

		tileX = 38;
		tileY = 16 - 15;
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
		int tileY = 15 - 15;
		int *tempTile = new int[6];
		tempTile[0] = x;
		tempTile[1] = 9;
		tempTile[2] = tileX;
		tempTile[3] = tileY;
		tempTile[4] = 1;
		tempTile[5] = 0;
		tiles.push_back(tempTile);

		tileY = 16 - 15;
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
			int tileY = y + 11 - 15;
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
			int tileY = y + 11 - 15;
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
			int tileY = y + 9 - 15;
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
		int tileY = 15 - 15;
		int *tempTile = new int[6];
		tempTile[0] = x;
		tempTile[1] = 9;
		tempTile[2] = tileX;
		tempTile[3] = tileY;
		tempTile[4] = 1;
		tempTile[5] = 0;
		tiles.push_back(tempTile);

		tileY = 16 - 15;
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
		int tileY = 15 - 15;
		int *tempTile = new int[6];
		tempTile[0] = x;
		tempTile[1] = 9;
		tempTile[2] = tileX;
		tempTile[3] = tileY;
		tempTile[4] = 0;
		tempTile[5] = 0;
		tiles.push_back(tempTile);

		tileX = 38;
		tileY = 16 - 15;
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
		int tileY = 17 - 15;
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

	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)barTop, barTop->xFrom + 40 );
	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)barTop, barTop->xTo - 40 );

	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)landRight, landRight->xFrom + 40 );
	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)landRight, ((landRight->xTo + landRight->xFrom) / 2));
	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)landRight, landRight->xTo - 40 );
	
	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_LEAFEYE, (int)landRight, NULL);
}

