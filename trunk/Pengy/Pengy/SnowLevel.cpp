#include "SnowLevel.h"
#include "Location.h"

SnowLevel::SnowLevel(void)
{
}

SnowLevel::~SnowLevel(void)
{
}

vector<Surface*> SnowLevel::GetSurfaces()
{
	vector<Surface*> surfaces;

	Surface * borderBottom = new Surface();
	borderBottom->xFrom = 0;
	borderBottom->xTo = 3779;
	borderBottom->yFrom = 662;
	borderBottom->yTo = 700;
	surfaces.push_back(borderBottom);

	Surface * borderLeft = new Surface();
	borderLeft->xFrom = 0;
	borderLeft->xTo = 8;
	borderLeft->yFrom = 0;
	borderLeft->yTo = 700;
	surfaces.push_back(borderLeft);	

	Surface * borderRight = new Surface();
	borderRight->xFrom = 3776;
	borderRight->xTo = 3779;
	borderRight->yFrom = 0;
	borderRight->yTo = 700;
	surfaces.push_back(borderRight);

	Surface * borderTop = new Surface();
	borderTop->xFrom = 0;
	borderTop->xTo = 3779;
	borderTop->yFrom = 0;
	borderTop->yTo = 8;
	surfaces.push_back(borderTop);

	Surface * slopeTop = new Surface();
	slopeTop->xFrom = 0;
	slopeTop->xTo = 525;
	slopeTop->yFrom = 325;
	slopeTop->yTo = 674;
	surfaces.push_back(slopeTop);

	Surface * slopeTopBar = new Surface();
	slopeTopBar->xFrom = 130;
	slopeTopBar->xTo = 510;
	slopeTopBar->yFrom = 145;
	slopeTopBar->yTo = 175;
	surfaces.push_back(slopeTopBar);

	Surface * bar2 = new Surface();
	bar2->xFrom = 790;
	bar2->xTo = 875;
	bar2->yFrom = 395;
	bar2->yTo = 425;
	surfaces.push_back(bar2);

	pGround1 = new Surface();
	pGround1->xFrom = 960;
	pGround1->xTo = 1225;
	pGround1->yFrom = 575;
	pGround1->yTo = 700;
	surfaces.push_back(pGround1);

	Surface * ladder1Step1 = new Surface();
	ladder1Step1->xFrom = 990;
	ladder1Step1->xTo = 1055;
	ladder1Step1->yFrom = 350;
	ladder1Step1->yTo = 360;
	ladder1Step1->isCloud = true;
	surfaces.push_back(ladder1Step1);

	Surface * ladder1Step2 = new Surface();
	ladder1Step2->xFrom = 990;
	ladder1Step2->xTo = 1055;
	ladder1Step2->yFrom = 315;
	ladder1Step2->yTo = 325;
	ladder1Step2->isCloud = true;
	surfaces.push_back(ladder1Step2);

	Surface * ladder1Step3 = new Surface();
	ladder1Step3->xFrom = 990;
	ladder1Step3->xTo = 1055;
	ladder1Step3->yFrom = 285;
	ladder1Step3->yTo = 295;
	ladder1Step3->isCloud = true;
	surfaces.push_back(ladder1Step3);

	Surface * ladder1Step4 = new Surface();
	ladder1Step4->xFrom = 990;
	ladder1Step4->xTo = 1055;
	ladder1Step4->yFrom = 255;
	ladder1Step4->yTo = 265;
	ladder1Step4->isCloud = true;
	surfaces.push_back(ladder1Step4);

	Surface * ladder1Step5 = new Surface();
	ladder1Step5->xFrom = 990;
	ladder1Step5->xTo = 1055;
	ladder1Step5->yFrom = 225;
	ladder1Step5->yTo = 235;
	ladder1Step5->isCloud = true;
	surfaces.push_back(ladder1Step5);

	Surface * ladder1Step6 = new Surface();
	ladder1Step6->xFrom = 990;
	ladder1Step6->xTo = 1055;
	ladder1Step6->yFrom = 195;
	ladder1Step6->yTo = 205;
	ladder1Step6->isCloud = true;
	surfaces.push_back(ladder1Step6);

	Surface * bar3 = new Surface();
	bar3->xFrom = 1173;
	bar3->xTo = 1258;
	bar3->yFrom = 270;
	bar3->yTo = 300;
	surfaces.push_back(bar3);

	Surface * bar4 = new Surface();
	bar4->xFrom = 1173;
	bar4->xTo = 1258;
	bar4->yFrom = 140;
	bar4->yTo = 170;
	surfaces.push_back(bar4);

	Surface * bar5 = new Surface();
	bar5->xFrom = 1495;
	bar5->xTo = 1580;
	bar5->yFrom = 270;
	bar5->yTo = 300;
	surfaces.push_back(bar5);
	
	pGround2 = new Surface();
	pGround2->xFrom = 1530;
	pGround2->xTo = 2180;
	pGround2->yFrom = 575;
	pGround2->yTo = 700;
	surfaces.push_back(pGround2);

	Surface * bar6 = new Surface();
	bar6->xFrom = 1750;
	bar6->xTo = 1835;
	bar6->yFrom = 463;
	bar6->yTo = 493;
	surfaces.push_back(bar6);

	Surface * bar7 = new Surface();
	bar7->xFrom = 1878;
	bar7->xTo = 1963;
	bar7->yFrom = 333;
	bar7->yTo = 363;
	surfaces.push_back(bar7);

	Surface * bar8 = new Surface();
	bar8->xFrom = 2006;
	bar8->xTo = 2091;
	bar8->yFrom = 203;
	bar8->yTo = 233;
	surfaces.push_back(bar8);

	pIce = new Surface();
	pIce->xFrom = 2180;
	pIce->xTo = 2749;
	pIce->yFrom = 590;
	pIce->yTo = 700;
	surfaces.push_back(pIce);

	pGround3 = new Surface();
	pGround3->xFrom = 2749;
	pGround3->xTo = 3776;
	pGround3->yFrom = 575;
	pGround3->yTo = 700;
	surfaces.push_back(pGround3);

	Surface * ladder2Step1 = new Surface();
	ladder2Step1->xFrom = 2910;
	ladder2Step1->xTo = 2975;
	ladder2Step1->yFrom = 474;
	ladder2Step1->yTo = 484;
	ladder2Step1->isCloud = true;
	surfaces.push_back(ladder2Step1);

	Surface * ladder2Step2 = new Surface();
	ladder2Step2->xFrom = 2910;
	ladder2Step2->xTo = 2975;
	ladder2Step2->yFrom = 446;
	ladder2Step2->yTo = 456;
	ladder2Step2->isCloud = true;
	surfaces.push_back(ladder2Step2);

	Surface * ladder2Step3 = new Surface();
	ladder2Step3->xFrom = 2910;
	ladder2Step3->xTo = 2975;
	ladder2Step3->yFrom = 415;
	ladder2Step3->yTo = 425;
	ladder2Step3->isCloud = true;
	surfaces.push_back(ladder2Step3);

	Surface * ladder2Step4 = new Surface();
	ladder2Step4->xFrom = 2910;
	ladder2Step4->xTo = 2975;
	ladder2Step4->yFrom = 385;
	ladder2Step4->yTo = 395;
	ladder2Step4->isCloud = true;
	surfaces.push_back(ladder2Step4);

	Surface * ladder2Step5 = new Surface();
	ladder2Step5->xFrom = 2910;
	ladder2Step5->xTo = 2975;
	ladder2Step5->yFrom = 354;
	ladder2Step5->yTo = 364;
	ladder2Step5->isCloud = true;
	surfaces.push_back(ladder2Step5);

	Surface * ladder2Step6 = new Surface();
	ladder2Step6->xFrom = 2910;
	ladder2Step6->xTo = 2975;
	ladder2Step6->yFrom = 323;
	ladder2Step6->yTo = 333;
	ladder2Step6->isCloud = true;
	surfaces.push_back(ladder2Step6);

	Surface * bar9 = new Surface();
	bar9->xFrom = 3095;
	bar9->xTo = 3180;
	bar9->yFrom = 268;
	bar9->yTo = 298;
	surfaces.push_back(bar9);

	return surfaces;
}

vector<int*> SnowLevel::GetTiles()
{
	vector<int*> tiles ;
	for(int x = 0; x < 16; x++)
	{
		int tileX = x + 16;
		for(int y = 0; y < 12;y++)
		{
			int *tempTile = new int[6];
			tempTile[0] = x + 11;
			tempTile[1] = y;
			tempTile[2] = tileX;
			tempTile[3] = y;
			tempTile[4] = 0;
			tempTile[5] = 3;
			tiles.push_back(tempTile);
		}
	}
	for(int x = 0; x < 11; x++)
	{
		for(int y = 0; y < 12;y++)
		{
			int *tempTile = new int[6];
			tempTile[0] = x ;
			tempTile[1] = y;
			tempTile[2] = 16;
			tempTile[3] = 0;
			tempTile[4] = 0;
			tempTile[5] = 3;
			tiles.push_back(tempTile);
		}
	}

	for(int x = 0; x < 59; x++)
	{
		for(int y = 6; y < 11;y++)
		{
			int tileX = x;
			int tileY = y + 5;
			int *tempTile = new int[6];
			tempTile[0] = x ;
			tempTile[1] = y;
			tempTile[2] = tileX;
			tempTile[3] = tileY;
			tempTile[4] = 1;
			tempTile[5] = 1;
			tiles.push_back(tempTile);
		}
	}

	for(int x = 0; x < 59; x++)
	{
		for(int y = 6; y < 11;y++)
		{
			int tileX = x;
			int tileY = y + 5;
			int *tempTile = new int[6];
			tempTile[0] = x + 5 ;
			tempTile[1] = y;
			tempTile[2] = tileX;
			tempTile[3] = tileY;
			tempTile[4] = 1;
			tempTile[5] = 2;
			tiles.push_back(tempTile);
		}
	}

	for(int x = 0; x < 15; x++)
	{
		for(int y = 5; y < 9;y++)
		{
			int tileX = x + 35;
			int tileY = y - 5;
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

	for(int x = 0; x < 19; x++)
	{
		int * tempTile1 = new int[6];
		int * tempTile2 = new int[6];
		int tileX1 = 32;
		int tileX2 = 32;
		int tileY1 = 4;
		int tileY2 = 5;
		tempTile1[0] = x;
		tempTile1[1] = 9;
		tempTile1[2] = tileX1;
		tempTile1[3] = tileY1;
		tempTile1[4] = 0;
		tempTile1[5] = 0;

		tempTile2[0] = x;
		tempTile2[1] = 10;
		tempTile2[2] = tileX1;
		tempTile2[3] = tileY2;
		tempTile2[4] = 0;
		tempTile2[5] = 0;
		tiles.push_back(tempTile1);
		tiles.push_back(tempTile2);
	}

	for(int x = 19; x<21; x++)
	{
		int * tempTile1 = new int[6];
		int * tempTile2 = new int[6];
		int tileX1 = 19+x;
		int tileX2 = 19+x;
		int tileY1 = 4;
		int tileY2 = 5;
		tempTile1[0] = x;
		tempTile1[1] = 9;
		tempTile1[2] = tileX1;
		tempTile1[3] = tileY1;
		tempTile1[4] = 1;
		tempTile1[5] = 0;

		tempTile2[0] = x;
		tempTile2[1] = 10;
		tempTile2[2] = tileX1;
		tempTile2[3] = tileY2;
		tempTile2[4] = 1;
		tempTile2[5] = 0;
		tiles.push_back(tempTile1);
		tiles.push_back(tempTile2);
	}

	for(int x = 22; x<24; x++)
	{
		int * tempTile1 = new int[6];
		int * tempTile2 = new int[6];
		int tileX1 = 18+x;
		int tileX2 = 18+x;
		int tileY1 = 4;
		int tileY2 = 5;
		tempTile1[0] = x;
		tempTile1[1] = 9;
		tempTile1[2] = tileX1;
		tempTile1[3] = tileY1;
		tempTile1[4] = 1;
		tempTile1[5] = 0;

		tempTile2[0] = x;
		tempTile2[1] = 10;
		tempTile2[2] = tileX1;
		tempTile2[3] = tileY2;
		tempTile2[4] = 1;
		tempTile2[5] = 0;
		tiles.push_back(tempTile1);
		tiles.push_back(tempTile2);
	}

	for(int x = 24; x < 34; x++)
	{
		int * tempTile1 = new int[6];
		int * tempTile2 = new int[6];
		int tileX1 = 32;
		int tileX2 = 32;
		int tileY1 = 4;
		int tileY2 = 5;
		tempTile1[0] = x;
		tempTile1[1] = 9;
		tempTile1[2] = tileX1;
		tempTile1[3] = tileY1;
		tempTile1[4] = 0;
		tempTile1[5] = 0;

		tempTile2[0] = x;
		tempTile2[1] = 10;
		tempTile2[2] = tileX1;
		tempTile2[3] = tileY2;
		tempTile2[4] = 0;
		tempTile2[5] = 0;
		tiles.push_back(tempTile1);
		tiles.push_back(tempTile2);
	}

	for(int x = 34; x < 36; x++)
	{
		int * tempTile1 = new int[6];
		int * tempTile2 = new int[6];
		int tileX1 = -1 + x;
		int tileX2 = -1 + x;
		int tileY1 = 4;
		int tileY2 = 5;
		tempTile1[0] = x;
		tempTile1[1] = 9;
		tempTile1[2] = tileX1;
		tempTile1[3] = tileY1;
		tempTile1[4] = 1;
		tempTile1[5] = 0;

		tempTile2[0] = x;
		tempTile2[1] = 10;
		tempTile2[2] = tileX1;
		tempTile2[3] = tileY2;
		tempTile2[4] = 1;
		tempTile2[5] = 0;
		tiles.push_back(tempTile1);
		tiles.push_back(tempTile2);
	}

	for(int x = 36; x < 41; x++)
	{
		int * tempTile1 = new int[6];
		int * tempTile2 = new int[6];
		int tileX1 = 35;
		int tileX2 = 35;
		int tileY1 = 4;
		int tileY2 = 5;
		tempTile1[0] = x;
		tempTile1[1] = 9;
		tempTile1[2] = tileX1;
		tempTile1[3] = tileY1;
		tempTile1[4] = 1;
		tempTile1[5] = 0;

		tempTile2[0] = x;
		tempTile2[1] = 10;
		tempTile2[2] = tileX1;
		tempTile2[3] = tileY2;
		tempTile2[4] = 1;
		tempTile2[5] = 0;
		tiles.push_back(tempTile1);
		tiles.push_back(tempTile2);
	}

	for(int x = 41; x < 43; x++)
	{
		int * tempTile1 = new int[6];
		int * tempTile2 = new int[6];
		int tileX1 = x - 5;
		int tileX2 = x - 5;
		int tileY1 = 4;
		int tileY2 = 5;
		tempTile1[0] = x;
		tempTile1[1] = 9;
		tempTile1[2] = tileX1;
		tempTile1[3] = tileY1;
		tempTile1[4] = 1;
		tempTile1[5] = 0;

		tempTile2[0] = x;
		tempTile2[1] = 10;
		tempTile2[2] = tileX1;
		tempTile2[3] = tileY2;
		tempTile2[4] = 1;
		tempTile2[5] = 0;
		tiles.push_back(tempTile1);
		tiles.push_back(tempTile2);
	}

	for(int x = 43; x < 60; x++)
	{
		int * tempTile1 = new int[6];
		int * tempTile2 = new int[6];
		int tileX1 = 32;
		int tileX2 = 32;
		int tileY1 = 4;
		int tileY2 = 5;
		tempTile1[0] = x;
		tempTile1[1] = 9;
		tempTile1[2] = tileX1;
		tempTile1[3] = tileY1;
		tempTile1[4] = 0;
		tempTile1[5] = 0;

		tempTile2[0] = x;
		tempTile2[1] = 10;
		tempTile2[2] = tileX1;
		tempTile2[3] = tileY2;
		tempTile2[4] = 0;
		tempTile2[5] = 0;
		tiles.push_back(tempTile1);
		tiles.push_back(tempTile2);
	}

	for(int x = 2; x<8; x++)
	{
		int y = 2;
		int tileX = 30 + x;
		int tileY = 6;
		int *tempTile = new int[6];
		tempTile[0] = x;
		tempTile[1] = y;
		tempTile[2] = tileX;
		tempTile[3] = tileY;
		tempTile[4] = 1;
		tempTile[5] = 0;
		tiles.push_back(tempTile);
	}

	for(int x = 12; x < 14; x++)
	{
		int y = 6;
		int tileX = 21 + x;
		int tileY = 0;
		int *tempTile = new int[6];
		tempTile[0] = x;
		tempTile[1] = y;
		tempTile[2] = tileX;
		tempTile[3] = tileY;
		tempTile[4] = 1;
		tempTile[5] = 0;
		tiles.push_back(tempTile);
	}

	for(int x = 18; x < 20; x++)
	{
		for(int y = 2 ; y < 6; y+=2)
		{
			int tileX = 15 + x;
			int tileY = 0;
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

	for(int x = 15; x < 17; x++)
	{
		for(int y = 2; y < 6; y++)
		{
			int tileX = x - 12;
			int tileY = y + 1;
			int * tempTile = new int[6];
			tempTile[0] = x;
			tempTile[1] = y;
			tempTile[2] = tileX;
			tempTile[3] = tileY;
			tempTile[4] = 1;
			tempTile[5] = 0;
			tiles.push_back(tempTile);
		}
	}

	for(int x = 23; x < 25; x++)
	{
		int y = 4;
		int tileX = 10 + x;
		int tileY = 0;
		int *tempTile = new int[6];
		tempTile[0] = x;
		tempTile[1] = y;
		tempTile[2] = tileX;
		tempTile[3] = tileY;
		tempTile[4] = 1;
		tempTile[5] = 0;
		tiles.push_back(tempTile);
	}

	for(int x = 27; x < 29; x++)
	{
		int y = 7;
		int tileX = 6 + x;
		int tileY = 0;
		int *tempTile = new int[6];
		tempTile[0] = x;
		tempTile[1] = y;
		tempTile[2] = tileX;
		tempTile[3] = tileY;
		tempTile[4] = 1;
		tempTile[5] = 0;
		tiles.push_back(tempTile);
	}

	for(int x = 29; x < 31; x++)
	{
		int y = 5;
		int tileX = 4 + x;
		int tileY = 0;
		int *tempTile = new int[6];
		tempTile[0] = x;
		tempTile[1] = y;
		tempTile[2] = tileX;
		tempTile[3] = tileY;
		tempTile[4] = 1;
		tempTile[5] = 0;
		tiles.push_back(tempTile);
	}

	for(int x = 31; x < 33; x++)
	{
		int y = 3;
		int tileX = 2 + x;
		int tileY = 0;
		int *tempTile = new int[6];
		tempTile[0] = x;
		tempTile[1] = y;
		tempTile[2] = tileX;
		tempTile[3] = tileY;
		tempTile[4] = 1;
		tempTile[5] = 0;
		tiles.push_back(tempTile);
	}

	for(int x = 48; x < 50; x++)
	{
		int y = 4;
		int tileX = x - 15;
		int tileY = 0;
		int *tempTile = new int[6];
		tempTile[0] = x;
		tempTile[1] = y;
		tempTile[2] = tileX;
		tempTile[3] = tileY;
		tempTile[4] = 1;
		tempTile[5] = 0;
		tiles.push_back(tempTile);
	}

	for(int x = 45; x < 47; x++)
	{
		for(int y = 4; y < 8; y++)
		{
			int tileX = x - 42;
			int tileY = y - 1;
			int * tempTile = new int[6];
			tempTile[0] = x;
			tempTile[1] = y;
			tempTile[2] = tileX;
			tempTile[3] = tileY;
			tempTile[4] = 1;
			tempTile[5] = 0;
			tiles.push_back(tempTile);
		}
	}

	return SortTiles(tiles);
}

void SnowLevel::LoadEnemies()
{
	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)pGround1, (int)pGround1->xTo - 10);
	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)pGround1, (int)pGround1->xFrom + 10);

	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)pGround2, (int)pGround2->xTo - 10);
	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)pGround2, (int)pGround2->xFrom + 0.5*(pGround2->xTo - pGround2->xFrom));
	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)pGround2, (int)pGround2->xFrom + 10);

	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)pIce, (int)pIce->xTo - 10);
	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)pIce, (int)pIce->xFrom + 10);

	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)pGround3, (int)pGround3->xTo - 10);
	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)pGround3, (int)pGround3->xFrom + 0.5*(pGround3->xTo - pGround3->xFrom));
	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)pGround3, (int)pGround3->xFrom + 10);
}

void SnowLevel::LoadGadgets()
{
	Location * pGl1 = new Location();
	Location * pGl2 = new Location();
	Location * pGl3 = new Location();
	Location * pGl4 = new Location();
	Location * pGl5 = new Location();
	Location * pGl6 = new Location();
	Location * pGl7 = new Location();
	Location * pGl8 = new Location();
	Location * pGl9 = new Location();
	Location * pGl10 = new Location();
	Location * pGl11 = new Location();
	Location * pGl12 = new Location();
	Location * pGl13 = new Location();
	Location * pGl14 = new Location();
	Location * pGl15 = new Location();
	Location * pGl16 = new Location();
	Location * pGl17 = new Location();

	pGl1->X = 170;
	pGl1->Y = 80;

	pGl2->X = 230;
	pGl2->Y = 80;

	pGl3->X = 290;
	pGl3->Y = 80;

	pGl4->X = 350;
	pGl4->Y = 80;

	pGl5->X = 410;
	pGl5->Y = 80;

	pGl6->X = 993;
	pGl6->Y = 307;

	pGl7->X = 993;
	pGl7->Y = 213;

	pGl8->X = 1080;
	pGl8->Y = 130;

	pGl9->X = 1185;
	pGl9->Y = 100;

	pGl10->X = 1192;
	pGl10->Y = 220;

	pGl11->X = 1501;
	pGl11->Y = 220;

	pGl12->X = 1765;
	pGl12->Y = 420;

	pGl13->X = 1885;
	pGl13->Y = 300;

	pGl14->X = 2005;
	pGl14->Y = 180;

	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pGl1, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pGl2, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pGl3, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pGl4, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pGl5, NULL);

	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_SNOWBALL, (int)pGl6, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_SNOWBALL, (int)pGl7, NULL);

	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pGl8, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_SWITCH, (int)pGl9, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_EXTRALIFE, (int)pGl10, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_SNOWBOOTS, (int)pGl11, NULL);

	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_SNOWBALL, (int)pGl12, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_SNOWBALL, (int)pGl13, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_SNOWBALL, (int)pGl14, NULL);
}
