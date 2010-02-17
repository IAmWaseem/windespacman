#pragma once

#include "View.h"
#include "Bitmap.h"
#include <windows.h>
#include <vector>
using namespace std;
using namespace dotnetguy;
#include "Tile.h"

class LevelView : public View
{
private:
	HANDLE tilemap;
	vector<Tile*> myTiles;
public:
	void Draw(HDC hDC, HWND m_hWnd);
	LevelView();
	~LevelView();
	void SetTiles(vector<Tile*> myTiles, LPCSTR path);
};
