#pragma once
#include "leveldata.h"

class ForestLevel : public LevelData
{
private:
	MovingSurface * movingSurface_1;
	MovingSurface * movingSurface_2;
	MovingSurface * movingSurface_3;
	MovingSurface * movingSurface_4;
	MovingSurface * movingSurface_5;
	Surface * landRight;
	Surface * barTop;

public:
	ForestLevel(void);
	~ForestLevel(void);
	void LoadGadgets();
	vector<Surface*> GetSurfaces();
	vector<int*> GetTiles();
	void LoadEnemies();
};
