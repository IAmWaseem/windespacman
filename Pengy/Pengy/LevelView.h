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
	static HANDLE tilemap;
	static vector<Tile*> * myTiles;
	void DrawTile(Tile * tile, HDC hdc, RECT rect);
	void DrawTile(Tile * tile, HDC hdc, RECT rect, int offsetX);
	void DrawTile(Tile * tile, HDC hdc, RECT rect, int offsetX, int offsetY);
public:
	void Draw(HDC hDC, int xFrom, int xTo);
	LevelView();
	~LevelView();
	void SetTiles(vector<Tile> myTiles, LPCSTR path);	
};
