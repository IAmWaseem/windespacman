#pragma once

#include "View.h"
#include <vector>
#include "Bitmap.h"
#include <windows.h>
#include "Surface.h"
#include "Tile.h"
#include <sstream>
using namespace std;
using namespace dotnetguy;

class LevelView : public View
{
private:
	static HANDLE tilemap;
	static HANDLE hbmMask;
	static int tilemapWidth;
	static int tilemapHeight;
	SYSTEMTIME st;
	static vector<Tile*> * myTiles;
	static vector<Surface*> * surfaces;
	void DrawTile(Tile * tile, HDC hdc, RECT rect);
	void DrawTile(Tile * tile, HDC hdc, RECT rect, int offsetX);
	void DrawTile(Tile * tile, HDC hdc, RECT rect, int offsetX, int offsetY);
	HANDLE CreateBitmapMask(HANDLE hbmColour, COLORREF crTransparent);
public:
	void Draw(HDC hDC, int xFrom, int xTo);
	LevelView();
	~LevelView();
	static bool ShowDebug;
	static bool ShowFps;
	void SetSurface(vector<Surface*> * theSurface);
	void SetTiles(vector<Tile> myTiles, LPCSTR path);	
};
