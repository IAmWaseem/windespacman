#pragma once
#include "LevelData.h"
using namespace std;

class BeachLevel : public LevelData
{
public:
	BeachLevel(void);
	~BeachLevel(void);

	void LoadGadgets();
	vector<Surface*> getSurfaces();
	vector<int*> getTiles();
private:
	vector<Surface*> * surfaces;
};
