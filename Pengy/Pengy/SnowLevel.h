#pragma once
#include "leveldata.h"
#include <vector>
using namespace std;

class SnowLevel :public LevelData
{
public:
	SnowLevel(void);
	~SnowLevel(void);
	void LoadGadgets();
	vector<Surface*> GetSurfaces();
	vector<int*> GetTiles();
	void LoadEnemies();
	vector<Surface*> * pSlopes;
private:
	Slopes cal;
	Surface * pGround1;
	Surface * pGround2;
	Surface * pIce;
	Surface * pGround3;
};
