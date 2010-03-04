#include "BeachLevel.h"



BeachLevel::BeachLevel(void)
{
	surfaces = new vector<Surface*>();

	Surface * borderBottom = new Surface();
	borderBottom->xFrom = 0;
	borderBottom->xTo = 2500;
	borderBottom->yFrom = 568;
	borderBottom->yTo = 600;
	surfaces->push_back(borderBottom);

	Surface * borderLeft = new Surface();
	borderLeft->xFrom = 0;
	borderLeft->xTo = 8;
	borderLeft->yFrom = 0;
	borderLeft->yTo = 600;
	surfaces->push_back(borderLeft);	

	Surface * borderRight = new Surface();
	borderRight->xFrom = 2481;
	borderRight->xTo = 2489;
	borderRight->yFrom = 0;
	borderRight->yTo = 600;
	surfaces->push_back(borderRight);

	Surface * borderTop = new Surface();
	borderTop->xFrom = 0;
	borderTop->xTo = 2500;
	borderTop->yFrom = 0;
	borderTop->yTo = 8;
	surfaces->push_back(borderTop);

	Surface * landLeft = new Surface();
	landLeft->xFrom = 0;
	landLeft->xTo = 320;
	landLeft->yFrom = 448;
	landLeft->yTo = 600;
	surfaces->push_back(landLeft);

	Surface * landRight = new Surface();
	landRight->xFrom = 704;
	landRight->xTo = 2500;
	landRight->yFrom = 448;
	landRight->yTo = 600;
	surfaces->push_back(landRight);	

	Surface * waterLeft = new Surface();
	waterLeft->xFrom = 320;
	waterLeft->xTo = 384;
	waterLeft->yFrom = 530;
	waterLeft->yTo = 600;
	surfaces->push_back(waterLeft);

	Surface * waterRight = new Surface();
	waterRight->xFrom = 640;
	waterRight->xTo = 704;
	waterRight->yFrom = 530;
	waterRight->yTo = 600;
	surfaces->push_back(waterRight);

	Surface * aboveWater = new Surface();
	aboveWater->xFrom = 404;
	aboveWater->xTo = 492;
	aboveWater->yFrom = 404;
	aboveWater->yTo = 428;
	surfaces->push_back(aboveWater);

	Surface * aboveWater2 = new Surface();
	aboveWater2->xFrom = 532;
	aboveWater2->xTo = 620;
	aboveWater2->yFrom = 340;
	aboveWater2->yTo = 364;
	surfaces->push_back(aboveWater2);

	Surface * firstObstacle = new Surface();
	firstObstacle->xFrom = 852;
	firstObstacle->xTo = 940;
	firstObstacle->yFrom = 340;
	firstObstacle->yTo = 364;
	surfaces->push_back(firstObstacle);

	Surface * secondObstacle = new Surface();
	secondObstacle->xFrom = 980;
	secondObstacle->xTo = 1068;
	secondObstacle->yFrom = 276;
	secondObstacle->yTo = 300;
	surfaces->push_back(secondObstacle);

	Surface * thirdObstacle = new Surface();
	thirdObstacle->xFrom = 1044;
	thirdObstacle->xTo = 1196;
	thirdObstacle->yFrom = 148;
	thirdObstacle->yTo = 172;
	surfaces->push_back(thirdObstacle);
}

BeachLevel::~BeachLevel(void)
{
}

void BeachLevel::LoadGadgets()
{
}

vector<Surface*> BeachLevel::getSurfaces()
{
	return *surfaces;
}


vector<int*> BeachLevel::getTiles()
{
	vector<int*> data;

#pragma region bottom ground
	// bottom data
	for(int i = 0; i < 39; i++)
	{
		int* temp = new int[6]; temp[0] = i; temp[1] = 7; temp[2] = 0; temp[3] = 7; temp[4] = 0; temp[5] = 0;
		data.push_back(temp);
	}
	// bottom data
	for(int i = 0; i < 39; i++)
	{
		int* temp = new int[6]; temp[0] = i; temp[1] = 8; temp[2] = 0; temp[3] = 8; temp[4] = 0; temp[5] = 0;
		data.push_back(temp);
	}
#pragma endregion here is the creation of the ground tiles

#pragma region waterpart

	// water part
	int* water1 = new int[6] ; water1[0] = 5; water1[1] = 7; water1[2] = 1; water1[3] = 7; water1[4] = 0; water1[5] = 0;
	int* water2 = new int[6] ; water2[0] = 5; water2[1] = 8; water2[2] = 1; water2[3] = 8; water2[4] = 0; water2[5] = 0;
	int* water3 = new int[6] ; water3[0] = 6; water3[1] = 7; water3[2] = 2; water3[3] = 7; water3[4] = 0; water3[5] = 0;
	int* water4 = new int[6] ; water4[0] = 6; water4[1] = 8; water4[2] = 2; water4[3] = 8; water4[4] = 0; water4[5] = 0;
	int* water5 = new int[6] ; water5[0] = 7; water5[1] = 7; water5[2] = 3; water5[3] = 7; water5[4] = 0; water5[5] = 0;
	int* water6 = new int[6] ; water6[0] = 7; water6[1] = 8; water6[2] = 3; water6[3] = 8; water6[4] = 0; water6[5] = 0;

	int* water9 = new int[6] ; water9[0] = 8; water9[1] = 7; water9[2] = 3; water9[3] = 7; water9[4] = 0;  water9[5] = 0;
	int* water10 = new int[6] ; water10[0] = 8; water10[1] = 8; water10[2] = 3; water10[3] = 8; water10[4] = 0; water10[5] = 0;
	int* water11 = new int[6] ; water11[0] = 9; water11[1] = 7; water11[2] = 3; water11[3] = 7; water11[4] = 0; water11[5] = 0;
	int* water12 = new int[6] ; water12[0] = 9; water12[1] = 8; water12[2] = 3; water12[3] = 8; water12[4] = 0; water12[5] = 0;

	int* water7 = new int[6] ; water7[0] = 10; water7[1] = 7; water7[2] = 4; water7[3] = 7; water7[4] = 0;water7[5] = 0;
	int* water8 = new int[6] ; water8[0] = 10; water8[1] = 8; water8[2] = 4; water8[3] = 8; water8[4] = 0;water8[5] = 0;
	data.push_back(water1); data.push_back(water2); data.push_back(water3); data.push_back(water4);
	data.push_back(water5); data.push_back(water6); data.push_back(water7); data.push_back(water8);
	data.push_back(water9); data.push_back(water10); data.push_back(water11); data.push_back(water12);

#pragma endregion here is the creation of the water tiles

#pragma region tree
	// note:
	// i is where the middle of the tree is!

	// big tree
	for(int i = 0; i < 20; i++)
	{
		if(i == 0 || i == 16 || i == 23)
		{
			// treeleaves
			int* tree1 = new int[6]; tree1[0] = -1 + (i); tree1[1] = 2; tree1[2] = 1; tree1[3] = 0; tree1[4] = 0;tree1[5] = 2;
			int* tree2 = new int[6]; tree2[0] =  0 + (i); tree2[1] = 2; tree2[2] = 2; tree2[3] = 0; tree2[4] = 0;	tree2[5] = 2;
			int* tree3 = new int[6]; tree3[0] =  1 + (i); tree3[1] = 2; tree3[2] = 3; tree3[3] = 0; tree3[4] = 0;tree3[5] = 2;
			int* tree4 = new int[6]; tree4[0] = -1 + (i); tree4[1] = 3; tree4[2] = 1; tree4[3] = 1; tree4[4] = 0;tree4[5] = 2;
			int* tree5 = new int[6]; tree5[0] =  0 + (i); tree5[1] = 3; tree5[2] = 2; tree5[3] = 1; tree5[4] = 0;tree5[5] = 2;
			int* tree6 = new int[6]; tree6[0] =  1 + (i); tree6[1] = 3; tree6[2] = 3; tree6[3] = 1; tree6[4] = 0;tree6[5] = 2;
			int* tree7 = new int[6]; tree7[0] = -1 + (i); tree7[1] = 4; tree7[2] = 1; tree7[3] = 2; tree7[4] = 0;tree7[5] = 2;
			int* tree8 = new int[6]; tree8[0] =  0 + (i); tree8[1] = 4; tree8[2] = 2; tree8[3] = 2; tree8[4] = 0;tree8[5] = 2;
			int* tree9 = new int[6]; tree9[0] =  1 + (i); tree9[1] = 4; tree9[2] = 3; tree9[3] = 2; tree9[4] = 0;tree9[5] = 2;

			// treelog
			int* tree10 = new int[6]; tree10[0] = 0 + (i); tree10[1] = 5; tree10[2] = 2; tree10[3] = 3; tree10[4] = 0;tree10[5] = 2;
			int* tree11 = new int[6]; tree11[0] = 0 + (i); tree11[1] = 6; tree11[2] = 2; tree11[3] = 4; tree11[4] = 0;tree11[5] = 2;

			data.push_back(tree1); data.push_back(tree2); data.push_back(tree3); 
			data.push_back(tree4); data.push_back(tree5); data.push_back(tree6); 
			data.push_back(tree7); data.push_back(tree8); data.push_back(tree9); 
			data.push_back(tree10); data.push_back(tree11);
		}
	}

	// medium tree
	for(int i = 0; i < 20; i++)
	{
		if(i == 11 || i == 19 || i == 25)
		{
			// treeleaves
			int* tree1 = new int[6]; tree1[0] = -1 + (i); tree1[1] = 3; tree1[2] = 5; tree1[3] = 4; tree1[4] = 1; tree1[5] = 1;
			int* tree2 = new int[6]; tree2[0] =  0 + (i); tree2[1] = 3; tree2[2] = 6; tree2[3] = 4; tree2[4] = 1; tree2[5] = 1;	
			int* tree3 = new int[6]; tree3[0] =  1 + (i); tree3[1] = 3; tree3[2] = 7; tree3[3] = 4; tree3[4] = 1; tree3[5] = 1;
			int* tree4 = new int[6]; tree4[0] = -1 + (i); tree4[1] = 4; tree4[2] = 5; tree4[3] = 5; tree4[4] = 1; tree4[5] = 1;
			int* tree5 = new int[6]; tree5[0] =  0 + (i); tree5[1] = 4; tree5[2] = 6; tree5[3] = 5; tree5[4] = 1; tree5[5] = 1;
			int* tree6 = new int[6]; tree6[0] =  1 + (i); tree6[1] = 4; tree6[2] = 7; tree6[3] = 5; tree6[4] = 1; tree6[5] = 1;

			// treelog
			int* tree10 = new int[6]; tree10[0] = 0 + (i); tree10[1] = 5; tree10[2] = 6; tree10[3] = 6; tree10[4] = 1; tree10[5] = 1;
			int* tree11 = new int[6]; tree11[0] = 0 + (i); tree11[1] = 6; tree11[2] = 6; tree11[3] = 7; tree11[4] = 1; tree11[5] = 1;

			data.push_back(tree1); data.push_back(tree2); data.push_back(tree3); 
			data.push_back(tree4); data.push_back(tree5); data.push_back(tree6); 
			data.push_back(tree10); data.push_back(tree11);
		}
	}

	// smallest tree
	for(int i = 0; i < 40; i++)
	{
		if(i == 2 || i == 17 || i == 24|| i == 27 || i == 34)
		{
			// treeleaves
			int* tree1 = new int[6]; tree1[0] = 0 + (i); tree1[1] = 3; tree1[2] = 0; tree1[3] = 3; tree1[4] = 1;tree1[5] = 0;
			int* tree2 = new int[6]; tree2[0] = 1 + (i); tree2[1] = 3; tree2[2] = 1; tree2[3] = 3; tree2[4] = 1;tree2[5] = 0;
			int* tree3 = new int[6]; tree3[0] = 0 + (i); tree3[1] = 4; tree3[2] = 0; tree3[3] = 4; tree3[4] = 1;tree3[5] = 0;
			int* tree4 = new int[6]; tree4[0] = 1 + (i); tree4[1] = 4; tree4[2] = 1; tree4[3] = 4; tree4[4] = 1;tree4[5] = 0;
			int* tree5 = new int[6]; tree5[0] = 0 + (i); tree5[1] = 5; tree5[2] = 0; tree5[3] = 5; tree5[4] = 1;tree5[5] = 0;
			int* tree6 = new int[6]; tree6[0] = 1 + (i); tree6[1] = 5; tree6[2] = 1; tree6[3] = 5; tree6[4] = 1;tree6[5] = 0;

			// treelog
			int* tree10 = new int[6]; tree10[0] = 0 + (i); tree10[1] = 6; tree10[2] = 0; tree10[3] = 6; tree10[4] = 1;tree10[5] = 0;
			int* tree11 = new int[6]; tree11[0] = 1 + (i); tree11[1] = 6; tree11[2] = 1; tree11[3] = 6; tree11[4] = 1;tree11[5] = 0;

			data.push_back(tree1); data.push_back(tree2); data.push_back(tree3); 
			data.push_back(tree4); data.push_back(tree5); data.push_back(tree6); 
			data.push_back(tree10); data.push_back(tree11);
		}
	}
#pragma endregion here is the creation of the tree tiles

#pragma region structures

	int* structure1 = new int[6]; structure1[0] = 6; structure1[1] = 6; structure1[2] = 5; structure1[3] = 3; structure1[4] = 1;structure1[5] = 0;
	data.push_back(structure1);

	int* structure2 = new int[6]; structure2[0] = 7; structure2[1] = 6; structure2[2] = 7; structure2[3] = 3; structure2[4] = 1;structure2[5] = 0;
	data.push_back(structure2);

	int* structure3 = new int[6]; structure3[0] = 8; structure3[1] = 5; structure3[2] = 5; structure3[3] = 3; structure3[4] = 1;structure3[5] = 0;
	data.push_back(structure3);

	int* structure4 = new int[6]; structure4[0] = 9; structure4[1] = 5; structure4[2] = 7; structure4[3] = 3; structure4[4] = 1;structure4[5] = 0;
	data.push_back(structure4);

	int* structure5 = new int[6]; structure5[0] = 15; structure5[1] = 4; structure5[2] = 5; structure5[3] = 3; structure5[4] = 1;structure5[5] = 0;
	data.push_back(structure5);

	int* structure6 = new int[6]; structure6[0] = 16; structure6[1] = 4; structure6[2] = 7; structure6[3] = 3; structure6[4] = 1;structure6[5] = 0;
	data.push_back(structure6);

	int* structure10 = new int[6]; structure10[0] = 13; structure10[1] = 5; structure10[2] = 5; structure10[3] = 3; structure10[4] = 1;structure10[5] = 0;
	data.push_back(structure10);

	int* structure11 = new int[6]; structure11[0] = 14; structure11[1] = 5; structure11[2] = 7; structure11[3] = 3; structure11[4] = 1;structure11[5] = 0;
	data.push_back(structure11);

	int* structure7 = new int[6]; structure7[0] = 16; structure7[1] = 2; structure7[2] = 5; structure7[3] = 3; structure7[4] = 1;structure7[5] = 0;
	data.push_back(structure7);

	int* structure8 = new int[6]; structure8[0] = 17; structure8[1] = 2; structure8[2] = 6; structure8[3] = 3; structure8[4] = 1;structure8[5] = 0;
	data.push_back(structure8);

	int* structure9 = new int[6]; structure9[0] = 18; structure9[1] = 2; structure9[2] = 7; structure9[3] = 3; structure9[4] = 1;structure9[5] = 0;
	data.push_back(structure9);

#pragma endregion creation of struction tiles

	vector<int*> data0;
	vector<int*> data1;
	vector<int*> data2;

	vector<int*>::iterator it;
	for(it=data.begin(); it!=data.end(); ++it)
	{
		int* dataRow = *it;
		if(dataRow[5] == 1)
		{
			data1.push_back(dataRow);
		}
		if(dataRow[5] == 2)
		{
			data2.push_back(dataRow);
		}
		else if(dataRow[5] == 0)
		{
			data0.push_back(dataRow);
		}
	}

	vector<int*> temp;

	vector<int*>::iterator it2;
	for(it2 = data2.begin(); it2 != data2.end(); ++it2)
	{
		int* dataRow = *it2;
		int* tempje = new int[6]; 
		tempje[0] = dataRow[0];
		tempje[1] = dataRow[1];
		tempje[2] = dataRow[2];
		tempje[3] = dataRow[3];
		tempje[4] = dataRow[4];
		tempje[5] = 2;
		temp.push_back(tempje);
	}

	vector<int*>::iterator it1;
	for(it1 = data1.begin(); it1 != data1.end(); ++it1)
	{
		int* dataRow = *it1;
		int* tempje = new int[6]; 
		tempje[0] = dataRow[0];
		tempje[1] = dataRow[1];
		tempje[2] = dataRow[2];
		tempje[3] = dataRow[3];
		tempje[4] = dataRow[4];
		tempje[5] = 1;
		temp.push_back(tempje);
	}

	vector<int*>::iterator it0;
	for(it0 = data0.begin(); it0 != data0.end(); ++it0)
	{
		int* dataRow = *it0;
		int* tempje = new int[6]; 
		tempje[0] = dataRow[0];
		tempje[1] = dataRow[1];
		tempje[2] = dataRow[2];
		tempje[3] = dataRow[3];
		tempje[4] = dataRow[4];
		tempje[5] = 0;
		temp.push_back(tempje);
	}

	return temp;
}

