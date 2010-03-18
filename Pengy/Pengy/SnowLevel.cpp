#include "SnowLevel.h"

SnowLevel::SnowLevel(void)
{
}

SnowLevel::~SnowLevel(void)
{
}

void SnowLevel::LoadGadgets()
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

	Surface * ground1 = new Surface();
	ground1->xFrom = 960;
	ground1->xTo = 1225;
	ground1->yFrom = 575;
	ground1->yTo = 700;
	surfaces.push_back(ground1);

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
