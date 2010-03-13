#include "LevelData.h"

LevelData::LevelData()
{
}

LevelData::~LevelData()
{
}

void LevelData::LoadGadgets()
{
}

vector<int*> LevelData::SortTiles(vector<int*> data)
{
	vector<int*> data0;
	vector<int*> data1;
	vector<int*> data2;
	vector<int*> data3;

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
		if(dataRow[5] == 3)
		{
			data3.push_back(dataRow);
		}
		else if(dataRow[5] == 0)
		{
			data0.push_back(dataRow);
		}
	}

	vector<int*> temp;

	vector<int*>::iterator it3;
	for(it3 = data3.begin(); it3 != data3.end(); ++it3)
	{
		int* dataRow = *it3;
		int* tempje = new int[6]; 
		tempje[0] = dataRow[0];
		tempje[1] = dataRow[1];
		tempje[2] = dataRow[2];
		tempje[3] = dataRow[3];
		tempje[4] = dataRow[4];
		tempje[5] = 3;
		temp.push_back(tempje);
	}

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

vector<Surface*> LevelData::GetSurfaces()
{
	vector<Surface*> data;
	return data;
}

vector<int*> LevelData::GetTiles()
{
	vector<int*> data;
	return data;
}
