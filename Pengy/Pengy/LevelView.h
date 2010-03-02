#pragma once

#include "View.h"
#include <vector>
#include "Bitmap.h"
#include <windows.h>
#include "Surface.h"
#include "Tile.h"
using namespace std;
using namespace dotnetguy;

class LevelView : public View
{
private:
	static HANDLE tilemap;
	static vector<Tile*> * myTiles;
	static vector<Surface*> * surfaces;
	void DrawTile(Tile * tile, HDC hdc, RECT rect);
	void DrawTile(Tile * tile, HDC hdc, RECT rect, int offsetX);
	void DrawTile(Tile * tile, HDC hdc, RECT rect, int offsetX, int offsetY);
	HBITMAP CreateBitmapMask(HBITMAP hbmColour, COLORREF crTransparent);
public:
	void Draw(HDC hDC, int xFrom, int xTo);
	LevelView();
	~LevelView();
	void SetSurface(vector<Surface*> * theSurface);
	void SetTiles(vector<Tile> myTiles, LPCSTR path);	
};
