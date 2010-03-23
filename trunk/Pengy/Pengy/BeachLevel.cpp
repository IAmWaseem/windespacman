#include "BeachLevel.h"
#include "Location.h"



BeachLevel::BeachLevel(void)
{
	pSurfaces = new vector<Surface*>();

	MovingSurface * ms = new MovingSurface(30, 150, 100, 170, 200, true);
	ms->isCloud = true;
	MessageQueue::Instance()->Attach(ms);
	pSurfaces->push_back(ms);

	Surface * borderBottom = new Surface();
	borderBottom->xFrom = 0;
	borderBottom->xTo = 3072;
	borderBottom->yFrom = 670;
	borderBottom->yTo = 700;
	borderBottom->isSurfaceOfDeath = true;
	pSurfaces->push_back(borderBottom);

	Surface * borderLeft = new Surface();
	borderLeft->xFrom = 0;
	borderLeft->xTo = 8;
	borderLeft->yFrom = -100;
	borderLeft->yTo = 700;
	pSurfaces->push_back(borderLeft);	

	Surface * borderRight = new Surface();
	borderRight->xFrom = 3053;
	borderRight->xTo = 3061;
	borderRight->yFrom = -100;
	borderRight->yTo = 700;
	pSurfaces->push_back(borderRight);

	Surface * borderTop = new Surface();
	borderTop->xFrom = 0;
	borderTop->xTo = 3072;
	borderTop->yFrom = -120;
	borderTop->yTo = -100;
	pSurfaces->push_back(borderTop);

	Surface * landLeft = new Surface();
	landLeft->xFrom = 0;
	landLeft->xTo = 320;
	landLeft->yFrom = 576;
	landLeft->yTo = 670;
	pSurfaces->push_back(landLeft);

	Surface * landRight = new Surface();
	landRight->xFrom = 704;
	landRight->xTo = 1920;
	landRight->yFrom = 576;
	landRight->yTo = 670;
	pSurfaces->push_back(landRight);	

	// two slopes for testing purposes

	/*Surface * slopeLeft = new Surface();
	slopeLeft->xFrom = 320;
	slopeLeft->xTo = 384;
	slopeLeft->yFrom = 449;
	slopeLeft->yTo = 530;
	slopeLeft->isSlope=1;
	slopeLeft->SlopeCoefficientA = cal.CalculateSlopCoeffA(320,449,384,530);
	slopeLeft->SlopeCoefficientB = cal.CalculateSlopCoeffB(320,448,slopeLeft->SlopeCoefficientA);
	pSurfaces->push_back(slopeLeft);*/

	/*Surface * slopeRight = new Surface();
	slopeRight->xFrom = 840;
	slopeRight->xTo = 904;
	slopeRight->yFrom = 449;
	slopeRight->yTo = 530;
	slopeRight->isSlope=2;
	slopeRight->SlopeCoefficientA = cal.CalculateSlopCoeffA(840,530,904,449);
	slopeRight->SlopeCoefficientB = cal.CalculateSlopCoeffB(840,530,slopeRight->SlopeCoefficientA);
	pSurfaces->push_back(slopeRight);*/

	//////////////////////////////////////////////////////////////////////////////
	// for letting the array be stil the same, indexes are used in the program	//
	Surface * waterLeft = new Surface();										//
	pSurfaces->push_back(waterLeft);											//
																				//
	Surface * waterRight = new Surface();										//
	pSurfaces->push_back(waterRight);											//
	//////////////////////////////////////////////////////////////////////////////

	Surface * aboveWater = new Surface();
	aboveWater->xFrom = 404;
	aboveWater->xTo = 492;
	aboveWater->yFrom = 532;
	aboveWater->yTo = 556;
	pSurfaces->push_back(aboveWater);

	Surface * aboveWater2 = new Surface();
	aboveWater2->xFrom = 532;
	aboveWater2->xTo = 620;
	aboveWater2->yFrom = 532;
	aboveWater2->yTo = 556;
	pSurfaces->push_back(aboveWater2);

	Surface * firstObstacle = new Surface();
	firstObstacle->xFrom = 852;
	firstObstacle->xTo = 940;
	firstObstacle->yFrom = 340;
	firstObstacle->yTo = 364;
	firstObstacle->isCloud = true;
	pSurfaces->push_back(firstObstacle);

	Surface * secondObstacle = new Surface();
	secondObstacle->xFrom = 980;
	secondObstacle->xTo = 1068;
	secondObstacle->yFrom = 276;
	secondObstacle->yTo = 300;
	secondObstacle->isCloud = true;
	pSurfaces->push_back(secondObstacle);

	Surface * thirdObstacle = new Surface();
	thirdObstacle->xFrom = 1044;
	thirdObstacle->xTo = 1132;
	thirdObstacle->yFrom = 340;
	thirdObstacle->yTo = 364;
	thirdObstacle->isCloud = true;
	pSurfaces->push_back(thirdObstacle);

	Surface * fifthObstacle = new Surface();
	fifthObstacle->xFrom = 1300;
	fifthObstacle->xTo = 1580;
	fifthObstacle->yFrom = 148;
	fifthObstacle->yTo = 172;
	fifthObstacle->isCloud = false;
	pSurfaces->push_back(fifthObstacle);

	// ladders
	Surface * ladderCloud1 = new Surface();
	ladderCloud1->xFrom = 1365;
	ladderCloud1->yFrom = 322;
	ladderCloud1->xTo = 1450;
	ladderCloud1->yTo = 329;
	ladderCloud1->isCloud = true;
	pSurfaces->push_back(ladderCloud1);

	Surface * ladderCloud2 = new Surface();
	ladderCloud2->xFrom = 1365;
	ladderCloud2->yFrom = 353;
	ladderCloud2->xTo = 1450;
	ladderCloud2->yTo = 360;
	ladderCloud2->isCloud = true;
	pSurfaces->push_back(ladderCloud2);

	Surface * ladderCloud3 = new Surface();
	ladderCloud3->xFrom = 1365;
	ladderCloud3->yFrom = 384;
	ladderCloud3->xTo = 1450;
	ladderCloud3->yTo = 391;
	ladderCloud3->isCloud = true;
	pSurfaces->push_back(ladderCloud3);

	Surface * ladderCloud4 = new Surface();
	ladderCloud4->xFrom = 1365;
	ladderCloud4->yFrom = 415;
	ladderCloud4->xTo = 1450;
	ladderCloud4->yTo = 422;
	ladderCloud4->isCloud = true;
	pSurfaces->push_back(ladderCloud4);

	Surface * ladderCloud5 = new Surface();
	ladderCloud5->xFrom = 1365;
	ladderCloud5->yFrom = 446;
	ladderCloud5->xTo = 1450;
	ladderCloud5->yTo = 454;
	ladderCloud5->isCloud = true;
	pSurfaces->push_back(ladderCloud5);

	Surface * ladderCloud6 = new Surface();
	ladderCloud6->xFrom = 1365;
	ladderCloud6->yFrom = 477;
	ladderCloud6->xTo = 1450;
	ladderCloud6->yTo = 485;
	ladderCloud6->isCloud = true;
	pSurfaces->push_back(ladderCloud6);

	// ladder 2
	
	Surface * ladderCloud9 = new Surface();
	ladderCloud9->xFrom = 1173;
	ladderCloud9->yFrom = 130;
	ladderCloud9->xTo = 1258;
	ladderCloud9->yTo = 137;
	ladderCloud9->isCloud = true;
	pSurfaces->push_back(ladderCloud9);

	Surface * ladderCloud10 = new Surface();
	ladderCloud10->xFrom = 1173;
	ladderCloud10->yFrom = 161;
	ladderCloud10->xTo = 1258;
	ladderCloud10->yTo = 168;
	ladderCloud10->isCloud = true;
	pSurfaces->push_back(ladderCloud10);

	Surface * ladderCloud11 = new Surface();
	ladderCloud11->xFrom = 1173;
	ladderCloud11->yFrom = 190;
	ladderCloud11->xTo = 1258;
	ladderCloud11->yTo = 198;
	ladderCloud11->isCloud = true;
	pSurfaces->push_back(ladderCloud11);

	Surface * ladderCloud12 = new Surface();
	ladderCloud12->xFrom = 1173;
	ladderCloud12->yFrom = 221;
	ladderCloud12->xTo = 1258;
	ladderCloud12->yTo = 229;
	ladderCloud12->isCloud = true;
	pSurfaces->push_back(ladderCloud12);	

	Surface * landRight2 = new Surface();
	landRight2->xFrom = 2496;
	landRight2->xTo = 3072;
	landRight2->yFrom = 576;
	landRight2->yTo = 670;
	pSurfaces->push_back(landRight2);

	bool first = true;
	for(int i = 0; i < 6; i++)
	{
		if(!first)
		{
			int tempX = 26 + i;
			int tempY = 6 - i;

			Surface * temp = new Surface();

			temp->xFrom = (tempX - 1) * 64 + 20;
			temp->xTo = (tempX + 1) * 64 - 20;			
			temp->yFrom = tempY * 64 + 20;
			temp->yTo = tempY * 64 + 45;

			temp->yFrom = temp->yFrom + 64;
			temp->yTo = temp->yTo + 64;

			pSurfaces->push_back(temp);
		}
		if(first)
			first = false;
		else
			first = true;
	}
}


BeachLevel::~BeachLevel(void)
{
}

vector<Surface*> BeachLevel::GetSurfaces()
{
	return *pSurfaces;
}

vector<int*> BeachLevel::GetTiles()
{
	vector<int*> data;

#pragma region bottom ground
	// bottom data
	for(int i = 0; i <= 47; i++)
	{
		int* temp = new int[6]; temp[0] = i; temp[1] = 9; temp[2] = 0; temp[3] = 7; temp[4] = 0; temp[5] = 0;
		data.push_back(temp);
	}
	// bottom data
	for(int i = 0; i <= 47; i++)
	{
		int* temp = new int[6]; temp[0] = i; temp[1] = 10; temp[2] = 0; temp[3] = 8; temp[4] = 0; temp[5] = 0;
		data.push_back(temp);
	}
#pragma endregion here is the creation of the ground tiles

#pragma region waterpart

	for(int i = 0; i < 2; i++)
	{
		int offset = 0;
		if(i == 1)
			offset = 25;
		// water part
		int* water1 = new int[6] ; water1[0] = 5 + offset; water1[1] = 9; water1[2] = 1; water1[3] = 7; water1[4] = 0; water1[5] = 0;
		int* water2 = new int[6] ; water2[0] = 5 + offset; water2[1] = 10; water2[2] = 1; water2[3] = 8; water2[4] = 0; water2[5] = 0;
		int* water3 = new int[6] ; water3[0] = 6 + offset; water3[1] = 9; water3[2] = 2; water3[3] = 7; water3[4] = 0; water3[5] = 0;
		int* water4 = new int[6] ; water4[0] = 6 + offset; water4[1] = 10; water4[2] = 2; water4[3] = 8; water4[4] = 0; water4[5] = 0;
		int* water5 = new int[6] ; water5[0] = 7 + offset; water5[1] = 9; water5[2] = 3; water5[3] = 7; water5[4] = 0; water5[5] = 0;
		int* water6 = new int[6] ; water6[0] = 7 + offset; water6[1] = 10; water6[2] = 3; water6[3] = 8; water6[4] = 0; water6[5] = 0;

		int* water9 = new int[6] ; water9[0] = 8 + offset; water9[1] = 9; water9[2] = 3; water9[3] = 7; water9[4] = 0;  water9[5] = 0;
		int* water10 = new int[6] ; water10[0] = 8 + offset; water10[1] = 10; water10[2] = 3; water10[3] = 8; water10[4] = 0; water10[5] = 0;
		int* water11 = new int[6] ; water11[0] = 9 + offset; water11[1] = 9; water11[2] = 2; water11[3] = 7; water11[4] = 0; water11[5] = 0;
		int* water12 = new int[6] ; water12[0] = 9 + offset; water12[1] = 10; water12[2] = 2; water12[3] = 8; water12[4] = 0; water12[5] = 0;
		
		int extraOffset = 0;
		if(i == 1)
		{
			for(int j = 0; j < 3; j++)
			{
				int* water13 = new int[6]; water13[0] = 10 + offset + extraOffset; water13[1] = 9; water13[2] = 3; water13[3] = 7; water13[4] = 0;  water13[5] = 0;
				int* water14 = new int[6]; water14[0] = 10 + offset + extraOffset; water14[1] = 10; water14[2] = 3; water14[3] = 8; water14[4] = 0;  water14[5] = 0;
				data.push_back(water13);data.push_back(water14);
				extraOffset = extraOffset + 1;
			}
			
		}

		int* water7 = new int[6] ; water7[0] = 10 + offset + extraOffset; water7[1] = 9; water7[2] = 4; water7[3] = 7; water7[4] = 0;water7[5] = 0;
		int* water8 = new int[6] ; water8[0] = 10 + offset + extraOffset; water8[1] = 10; water8[2] = 4; water8[3] = 8; water8[4] = 0;water8[5] = 0;
		data.push_back(water1); data.push_back(water2); data.push_back(water3); data.push_back(water4);
		data.push_back(water5); data.push_back(water6); data.push_back(water7); data.push_back(water8);
		data.push_back(water9); data.push_back(water10); data.push_back(water11); data.push_back(water12);
	}

#pragma endregion here is the creation of the water tiles

#pragma region tree
	// note:
	// i is where the middle of the tree is!

	// big tree
	for(int i = 0; i <= 47; i++)
	{
		if(i == 0 || i == 16 || i == 31)
		{
			// treeleaves
			int* tree1 = new int[6]; tree1[0] = -1 + (i); tree1[1] = 4; tree1[2] = 1; tree1[3] = 0; tree1[4] = 1;tree1[5] = 2;
			int* tree2 = new int[6]; tree2[0] =  0 + (i); tree2[1] = 4; tree2[2] = 2; tree2[3] = 0; tree2[4] = 1;	tree2[5] = 2;
			int* tree3 = new int[6]; tree3[0] =  1 + (i); tree3[1] = 4; tree3[2] = 3; tree3[3] = 0; tree3[4] = 1;tree3[5] = 2;
			int* tree4 = new int[6]; tree4[0] = -1 + (i); tree4[1] = 5; tree4[2] = 1; tree4[3] = 1; tree4[4] = 1;tree4[5] = 2;
			int* tree5 = new int[6]; tree5[0] =  0 + (i); tree5[1] = 5; tree5[2] = 2; tree5[3] = 1; tree5[4] = 1;tree5[5] = 2;
			int* tree6 = new int[6]; tree6[0] =  1 + (i); tree6[1] = 5; tree6[2] = 3; tree6[3] = 1; tree6[4] = 1;tree6[5] = 2;
			int* tree7 = new int[6]; tree7[0] = -1 + (i); tree7[1] = 6; tree7[2] = 1; tree7[3] = 2; tree7[4] = 1;tree7[5] = 2;
			int* tree8 = new int[6]; tree8[0] =  0 + (i); tree8[1] = 6; tree8[2] = 2; tree8[3] = 2; tree8[4] = 1;tree8[5] = 2;
			int* tree9 = new int[6]; tree9[0] =  1 + (i); tree9[1] = 6; tree9[2] = 3; tree9[3] = 2; tree9[4] = 1;tree9[5] = 2;

			// treelog
			int* tree10 = new int[6]; tree10[0] = 0 + (i); tree10[1] = 7; tree10[2] = 2; tree10[3] = 3; tree10[4] = 1;tree10[5] = 2;
			int* tree11 = new int[6]; tree11[0] = 0 + (i); tree11[1] = 8; tree11[2] = 2; tree11[3] = 4; tree11[4] = 1;tree11[5] = 2;

			data.push_back(tree1); data.push_back(tree2); data.push_back(tree3); 
			data.push_back(tree4); data.push_back(tree5); data.push_back(tree6); 
			data.push_back(tree7); data.push_back(tree8); data.push_back(tree9); 
			data.push_back(tree10); data.push_back(tree11);
		}
	}

	// medium tree
	for(int i = 0; i <= 47; i++)
	{
		if(i == 11 || i == 19)
		{
			// treeleaves
			int* tree1 = new int[6]; tree1[0] = -1 + (i); tree1[1] = 5; tree1[2] = 5; tree1[3] = 4; tree1[4] = 1; tree1[5] = 2;
			int* tree2 = new int[6]; tree2[0] =  0 + (i); tree2[1] = 5; tree2[2] = 6; tree2[3] = 4; tree2[4] = 1; tree2[5] = 2;	
			int* tree3 = new int[6]; tree3[0] =  1 + (i); tree3[1] = 5; tree3[2] = 7; tree3[3] = 4; tree3[4] = 1; tree3[5] = 2;
			int* tree4 = new int[6]; tree4[0] = -1 + (i); tree4[1] = 6; tree4[2] = 5; tree4[3] = 5; tree4[4] = 1; tree4[5] = 2;
			int* tree5 = new int[6]; tree5[0] =  0 + (i); tree5[1] = 6; tree5[2] = 6; tree5[3] = 5; tree5[4] = 1; tree5[5] = 2;
			int* tree6 = new int[6]; tree6[0] =  1 + (i); tree6[1] = 6; tree6[2] = 7; tree6[3] = 5; tree6[4] = 1; tree6[5] = 2;

			// treelog
			int* tree10 = new int[6]; tree10[0] = 0 + (i); tree10[1] = 7; tree10[2] = 6; tree10[3] = 6; tree10[4] = 1; tree10[5] = 2;
			int* tree11 = new int[6]; tree11[0] = 0 + (i); tree11[1] = 8; tree11[2] = 6; tree11[3] = 7; tree11[4] = 1; tree11[5] = 2;

			data.push_back(tree1); data.push_back(tree2); data.push_back(tree3); 
			data.push_back(tree4); data.push_back(tree5); data.push_back(tree6); 
			data.push_back(tree10); data.push_back(tree11);
		}
	}

	// smallest tree
	for(int i = 0; i <= 47; i++)
	{
		if(i == 2 || i == 17 || i == 34)
		{
			// treeleaves
			int* tree1 = new int[6]; tree1[0] = 0 + (i); tree1[1] = 5; tree1[2] = 0; tree1[3] = 3; tree1[4] = 1;tree1[5] = 1;
			int* tree2 = new int[6]; tree2[0] = 1 + (i); tree2[1] = 5; tree2[2] = 1; tree2[3] = 3; tree2[4] = 1;tree2[5] = 1;
			int* tree3 = new int[6]; tree3[0] = 0 + (i); tree3[1] = 6; tree3[2] = 0; tree3[3] = 4; tree3[4] = 1;tree3[5] = 1;
			int* tree4 = new int[6]; tree4[0] = 1 + (i); tree4[1] = 6; tree4[2] = 1; tree4[3] = 4; tree4[4] = 1;tree4[5] = 1;
			int* tree5 = new int[6]; tree5[0] = 0 + (i); tree5[1] = 7; tree5[2] = 0; tree5[3] = 5; tree5[4] = 1;tree5[5] = 1;
			int* tree6 = new int[6]; tree6[0] = 1 + (i); tree6[1] = 7; tree6[2] = 1; tree6[3] = 5; tree6[4] = 1;tree6[5] = 1;

			// treelog
			int* tree10 = new int[6]; tree10[0] = 0 + (i); tree10[1] = 8; tree10[2] = 0; tree10[3] = 6; tree10[4] = 1;tree10[5] = 1;
			int* tree11 = new int[6]; tree11[0] = 1 + (i); tree11[1] = 8; tree11[2] = 1; tree11[3] = 6; tree11[4] = 1;tree11[5] = 1;

			data.push_back(tree1); data.push_back(tree2); data.push_back(tree3); 
			data.push_back(tree4); data.push_back(tree5); data.push_back(tree6); 
			data.push_back(tree10); data.push_back(tree11);
		}
	}
#pragma endregion here is the creation of the tree tiles

#pragma region decals

	int* decal1 = new int[6]; decal1[0] = 4; decal1[1] = 6; decal1[2] = 12; decal1[3] = 4; decal1[4] = 1; decal1[5] = 0;
	int* decal2 = new int[6]; decal2[0] = 4; decal2[1] = 7; decal2[2] = 12; decal2[3] = 5; decal2[4] = 1; decal2[5] = 0;
	int* decal3 = new int[6]; decal3[0] = 4; decal3[1] = 8; decal3[2] = 12; decal3[3] = 6; decal3[4] = 1; decal3[5] = 0;

	int* decal4 = new int[6]; decal4[0] = 5; decal4[1] = 6; decal4[2] = 13; decal4[3] = 4; decal4[4] = 1; decal4[5] = 0;
	int* decal5 = new int[6]; decal5[0] = 5; decal5[1] = 7; decal5[2] = 13; decal5[3] = 5; decal5[4] = 1; decal5[5] = 0;
	int* decal6 = new int[6]; decal6[0] = 5; decal6[1] = 8; decal6[2] = 13; decal6[3] = 6; decal6[4] = 1; decal6[5] = 0;
	data.push_back(decal1);data.push_back(decal2);data.push_back(decal3);
	data.push_back(decal4);data.push_back(decal5);data.push_back(decal6);

	for(int i = 0; i < 4; i++)
	{
		int* parasol3 = new int[6]; parasol3[0] = 24+i; parasol3[1] = 5; parasol3[2] = 12+i; parasol3[3] = 0; parasol3[4] = 1; parasol3[5] = 0;
		int* parasol4 = new int[6]; parasol4[0] = 24+i; parasol4[1] = 6; parasol4[2] = 12+i; parasol4[3] = 1; parasol4[4] = 1; parasol4[5] = 0;
		
		if(i > 0)
		{
			int* parasol5 = new int[6]; parasol5[0] = 24+i; parasol5[1] = 7; parasol5[2] = 12+i; parasol5[3] = 2; parasol5[4] = 1; parasol5[5] = 0;
			data.push_back(parasol5); 
		}
		if(i == 1)
		{
			int* parasol6 = new int[6]; parasol6[0] = 24+i; parasol6[1] = 8; parasol6[2] = 12+i; parasol6[3] = 3; parasol6[4] = 1; parasol6[5] = 0;
			data.push_back(parasol6);
		}		
		data.push_back(parasol3); data.push_back(parasol4); 
	}
	
#pragma endregion here is the creation of the decals

#pragma region clouds

	int* cloud1 = new int[6]; cloud1[0] = 6; cloud1[1] = 0; cloud1[2] = 4; cloud1[3] = 1; cloud1[4] = 0; cloud1[5] = 3;
	int* cloud2 = new int[6]; cloud2[0] = 7; cloud2[1] = 0; cloud2[2] = 5; cloud2[3] = 1; cloud2[4] = 0; cloud2[5] = 3;
	int* cloud3 = new int[6]; cloud3[0] = 8; cloud3[1] = 0; cloud3[2] = 6; cloud3[3] = 1; cloud3[4] = 0; cloud3[5] = 3;
	int* cloud4 = new int[6]; cloud4[0] = 9; cloud4[1] = 0; cloud4[2] = 7; cloud4[3] = 1; cloud4[4] = 0; cloud4[5] = 3;

	int* cloud5 = new int[6]; cloud5[0] = 6; cloud5[1] = 1; cloud5[2] = 4; cloud5[3] = 2; cloud5[4] = 0; cloud5[5] = 3;
	int* cloud6 = new int[6]; cloud6[0] = 7; cloud6[1] = 1; cloud6[2] = 5; cloud6[3] = 2; cloud6[4] = 0; cloud6[5] = 3;
	int* cloud7 = new int[6]; cloud7[0] = 8; cloud7[1] = 1; cloud7[2] = 6; cloud7[3] = 2; cloud7[4] = 0; cloud7[5] = 3;
	int* cloud8 = new int[6]; cloud8[0] = 9; cloud8[1] = 1; cloud8[2] = 7; cloud8[3] = 2; cloud8[4] = 0; cloud8[5] = 3;

	data.push_back(cloud1); data.push_back(cloud2); data.push_back(cloud3); data.push_back(cloud4);
	data.push_back(cloud5); data.push_back(cloud6); data.push_back(cloud7); data.push_back(cloud8);	
	
	int* cloud9 = new int[6]; cloud9[0] = 17; cloud9[1] = 1; cloud9[2] = 8; cloud9[3] = 5; cloud9[4] = 0; cloud9[5] = 3;
	int* cloud10 = new int[6]; cloud10[0] = 18; cloud10[1] = 1; cloud10[2] = 9; cloud10[3] = 5; cloud10[4] = 0; cloud10[5] = 3;
	int* cloud11 = new int[6]; cloud11[0] = 17; cloud11[1] = 2; cloud11[2] = 8; cloud11[3] = 6; cloud11[4] = 0; cloud11[5] = 3;
	int* cloud12 = new int[6]; cloud12[0] = 18; cloud12[1] = 2; cloud12[2] = 9; cloud12[3] = 6; cloud12[4] = 0; cloud12[5] = 3;

	data.push_back(cloud9); data.push_back(cloud10); data.push_back(cloud11); data.push_back(cloud12);

#pragma endregion

#pragma region structures

	int* structure1 = new int[6]; structure1[0] = 6; structure1[1] = 8; structure1[2] = 12; structure1[3] = 7; structure1[4] = 1; structure1[5] = 0;
	data.push_back(structure1);

	int* structure2 = new int[6]; structure2[0] = 7; structure2[1] = 8; structure2[2] = 14; structure2[3] = 7; structure2[4] = 1; structure2[5] = 0;
	data.push_back(structure2);

	int* structure3 = new int[6]; structure3[0] = 8; structure3[1] = 8; structure3[2] = 12; structure3[3] = 7; structure3[4] = 1; structure3[5] = 0;
	data.push_back(structure3);

	int* structure4 = new int[6]; structure4[0] = 9; structure4[1] = 8; structure4[2] = 14; structure4[3] = 7; structure4[4] = 1; structure4[5] = 0;
	data.push_back(structure4);

	int* structure5 = new int[6]; structure5[0] = 15; structure5[1] = 4; structure5[2] = 5; structure5[3] = 3; structure5[4] = 1; structure5[5] = 0;
	data.push_back(structure5);

	int* structure6 = new int[6]; structure6[0] = 16; structure6[1] = 4; structure6[2] = 7; structure6[3] = 3; structure6[4] = 1; structure6[5] = 0;
	data.push_back(structure6);

	int* structure9 = new int[6]; structure9[0] = 13; structure9[1] = 5; structure9[2] = 5; structure9[3] = 3; structure9[4] = 1; structure9[5] = 0;
	data.push_back(structure9);

	int* structure10 = new int[6]; structure10[0] = 14; structure10[1] = 5; structure10[2] = 7; structure10[3] = 3; structure10[4] = 1; structure10[5] = 0;
	data.push_back(structure10);

	int* structure7 = new int[6]; structure7[0] = 16; structure7[1] = 5; structure7[2] = 5; structure7[3] = 3; structure7[4] = 1; structure7[5] = 0;
	data.push_back(structure7);

	int* structure8 = new int[6]; structure8[0] = 17; structure8[1] = 5; structure8[2] = 7; structure8[3] = 3; structure8[4] = 1; structure8[5] = 0;
	data.push_back(structure8);

	int* structure13 = new int[6]; structure13[0] = 20; structure13[1] = 2; structure13[2] = 12; structure13[3] = 7; structure13[4] = 1; structure13[5] = 0;
	data.push_back(structure13);

	int* structure14 = new int[6]; structure14[0] = 21; structure14[1] = 2; structure14[2] = 13; structure14[3] = 7; structure14[4] = 1; structure14[5] = 0;
	data.push_back(structure14);

	int* structure15 = new int[6]; structure15[0] = 22; structure15[1] = 2; structure15[2] = 13; structure15[3] = 7; structure15[4] = 1; structure15[5] = 0;
	data.push_back(structure15);

	int* structure16 = new int[6]; structure16[0] = 23; structure16[1] = 2; structure16[2] = 13; structure16[3] = 7; structure16[4] = 1; structure16[5] = 0;
	data.push_back(structure16);

	int* structure17 = new int[6]; structure17[0] = 24; structure17[1] = 2; structure17[2] = 14; structure17[3] = 7; structure17[4] = 1; structure17[5] = 0;
	data.push_back(structure17);



	//ladder 1

	int* structure18 = new int[6]; structure18[0] = 18; structure18[1] = 1; structure18[2] = 3; structure18[3] = 3; structure18[4] = 1; structure18[5] = 0;
	data.push_back(structure18);

	int* structure19 = new int[6]; structure19[0] = 19; structure19[1] = 1; structure19[2] = 4; structure19[3] = 3; structure19[4] = 1; structure19[5] = 0;
	data.push_back(structure19);

	int* structure20 = new int[6]; structure20[0] = 18; structure20[1] = 2; structure20[2] = 3; structure20[3] = 4; structure20[4] = 1; structure20[5] = 0;
	data.push_back(structure20);

	int* structure21 = new int[6]; structure21[0] = 19; structure21[1] = 2; structure21[2] = 4; structure21[3] = 4; structure21[4] = 1; structure21[5] = 0;
	data.push_back(structure21);

	int* structure24 = new int[6]; structure24[0] = 18; structure24[1] = 3; structure24[2] = 3; structure24[3] = 6; structure24[4] = 1; structure24[5] = 0;
	data.push_back(structure24);

	int* structure25 = new int[6]; structure25[0] = 19; structure25[1] = 3; structure25[2] = 4; structure25[3] = 6; structure25[4] = 1; structure25[5] = 0;
	data.push_back(structure25);

	//ladder 2
	int* structure26 = new int[6]; structure26[0] = 21; structure26[1] = 4; structure26[2] = 3; structure26[3] = 3; structure26[4] = 1; structure26[5] = 0;
	data.push_back(structure26);

	int* structure27 = new int[6]; structure27[0] = 22; structure27[1] = 4; structure27[2] = 4; structure27[3] = 3; structure27[4] = 1; structure27[5] = 0;
	data.push_back(structure27);

	int* structure28 = new int[6]; structure28[0] = 21; structure28[1] = 5; structure28[2] = 3; structure28[3] = 4; structure28[4] = 1; structure28[5] = 0;
	data.push_back(structure28);

	int* structure29 = new int[6]; structure29[0] = 22; structure29[1] = 5; structure29[2] = 4; structure29[3] = 4; structure29[4] = 1; structure29[5] = 0;
	data.push_back(structure29);

	int* structure30 = new int[6]; structure30[0] = 21; structure30[1] = 6; structure30[2] = 3; structure30[3] = 5; structure30[4] = 1; structure30[5] = 0;
	data.push_back(structure30);

	int* structure31 = new int[6]; structure31[0] = 22; structure31[1] = 6; structure31[2] = 4; structure31[3] = 5; structure31[4] = 1; structure31[5] = 0;
	data.push_back(structure31);

	int* structure32 = new int[6]; structure32[0] = 21; structure32[1] = 7; structure32[2] = 3; structure32[3] = 6; structure32[4] = 1; structure32[5] = 0;
	data.push_back(structure32);

	int* structure33 = new int[6]; structure33[0] = 22; structure33[1] = 7; structure33[2] = 4; structure33[3] = 6; structure33[4] = 1; structure33[5] = 0;
	data.push_back(structure33);

	bool first = true;
	int height = 0;
	for(int i = 0; i < 6; i++)
	{
		int* tempstruc = new int[6];
		tempstruc[0] = 26 + i;
		tempstruc[1] = 6 - height;

		if(first)
		{
			tempstruc[2] = 12;
			first = false;
		}
		else
		{
			tempstruc[2] = 14;
			int tempheight = 2;
			if(tempheight > 3)
				tempheight = 3;
			height += tempheight;
			
			first = true;
		}

		tempstruc[3] = 7;
		tempstruc[4] = 1;
		tempstruc[5] = 0;
		data.push_back(tempstruc);
	}

#pragma endregion creation of struction tiles

	data = SortTiles(data);
	return data;
}

void BeachLevel::LoadEnemies()
{
	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)pSurfaces->at(6), (pSurfaces->at(6)->xFrom + pSurfaces->at(6)->xTo) / 2 + 10 );
	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)pSurfaces->at(25), (pSurfaces->at(25)->xFrom + pSurfaces->at(25)->xTo) / 4 + 10 );
	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)pSurfaces->at(6), (pSurfaces->at(6)->xTo) - 10 );
	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_WANDER, (int)pSurfaces->at(6), (pSurfaces->at(6)->xFrom) + 10 );
	MessageQueue::Instance()->SendMessage(CM_ENEMYFACTORY_CREATE_WALDO_PATROL, (int)pSurfaces->at(14), NULL);
}

void BeachLevel::LoadGadgets()
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

	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_PIRANHA, (int)pL1, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pL2, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pL3, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pL4, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)pL5, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_PIRANHA, (int)pL6, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_PIRANHA, (int)pL7, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_PIRANHA, (int)pL8, NULL);
	MessageQueue::Instance()->SendMessage(CM_GADGETFACTORY_CREATE_PIRANHA, (int)pL9, NULL);
}
