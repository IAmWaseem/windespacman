#pragma once

#ifndef _WINDOWS_
#include <windows.h>
#endif

#include <vector>
#include <iostream>
#include <algorithm>
#include "tile.h"
#include "Bitmap.h"

using namespace std;
using namespace dotnetguy;

class TileManager
{
public:
	TileManager(void);
	TileManager(LPCTSTR pathOfTileMap);
	~TileManager(void);
	void AddTile(Tile aTile);
	void AddTile(int pGridX, int pGridY, int pTileX, int pTileY);
	void AddTile(int pGridX, int pGridY, int pTileX, int pTileY, bool pTransparant);
	void DrawTile(int screenColX, int screenColY, int tileColX, int tileColY, HDC hdc, RECT rect);
	void ClearTiles();
	void RenderTiles(HDC hdc, RECT rect);
private:
	LPCTSTR Path;
	vector <Tile> mTiles;
	Bitmap tilemap;
	HANDLE tileset;
};
