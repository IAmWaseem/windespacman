#pragma once
#include "LevelData.h"
using namespace std;

class BeachLevel : public LevelData
{
public:
	BeachLevel(void);
	~BeachLevel(void);

	void LoadGadgets();
	vector<Surface*> GetSurfaces();
	vector<int*> GetTiles();
	void LoadEnemies();
private:
	//Slopes cal;
	vector<Surface*> * pSurfaces;
};
