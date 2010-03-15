#pragma once

#include "View.h"
#include <vector>
#include <windows.h>
#include "Surface.h"
#include "Renderer.h"
#include "Tile.h"
#include "MovingSurface.h"
#include <sstream>
using namespace std;

class LevelView : public View
{
private:
	static HANDLE tilemap;
	static HANDLE myMask;
	static int tilemapWidth;
	static int tilemapHeight;
	SYSTEMTIME st;
	static vector<Tile*> * myTiles;
	static vector<Surface*> * surfaces;
	void DrawTile(Tile * tile, HDC hdc, RECT rect);
	void DrawTile(Tile * tile, HDC hdc, RECT rect, int offsetX);
	void DrawTile(Tile * tile, HDC hdc, RECT rect, int offsetX, int offsetY);
public:
	void Draw(HDC hDC, RECT rect, int xFrom, int xTo);
	LevelView();
	~LevelView();
	void SetSurface(vector<Surface*> * theSurface);
	void SetTiles(vector<Tile> myTiles, LPCSTR path);	
	void StartGame();
};
