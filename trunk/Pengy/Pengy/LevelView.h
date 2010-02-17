#pragma once

#include "View.h"
#include "Bitmap.h"
#include <windows.h>
#include <vector>
using namespace std;
using namespace dotnetguy;

class LevelView : public View
{
private:
	vector<int*> myTiles;
public:
	void Draw(HDC hDC);
	LevelView();
	~LevelView();
	void SetTiles(vector<int*> myTiles);
};
