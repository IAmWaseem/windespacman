#include "TileManager.h"

// stuff that _should_ have been defined in some header :-/
#ifndef C1_TRANSPARENT
    #define C1_TRANSPARENT 0x0001
#endif 
#ifndef CAPS1
    #define CAPS1 94
#endif 
#ifndef NEWTRANSPARENT
    #define NEWTRANSPARENT 3
#endif

TileManager::TileManager(void)
{
	tilemap.DeleteObject();
	
	
}
TileManager::TileManager(LPCTSTR pathOfTileMap)
{
	tilemap.DeleteObject();
	Path = pathOfTileMap;	
	tileset = LoadImage(NULL, pathOfTileMap, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}
TileManager::~TileManager(void)
{
	tilemap.DeleteObject();
}
void TileManager::ClearTiles()
{
	mTiles.clear();
}
void TileManager::AddTile(Tile aTile)
{
	mTiles.push_back(aTile);
}
void TileManager::AddTile(int pGridX, int pGridY, int pTileX, int pTileY)
{
	mTiles.push_back(Tile(pGridX, pGridY, pTileX, pTileY));
}
void TileManager::AddTile(int pGridX, int pGridY, int pTileX, int pTileY, bool pTransparant)
{
	mTiles.push_back(Tile(pGridX, pGridY, pTileX, pTileY, pTransparant));
}
void TileManager::RenderTiles(HDC hdc, RECT rect)
{
	if(Path != NULL)
	{
		tilemap.LoadDIBFile(Path);
		for each (Tile lTile in mTiles)
		{
			if(lTile.Transparant == true)
				tilemap.TransparentPaintTile(hdc, RGB(0,0,0), lTile.GridX, lTile.GridY, lTile.TileX, lTile.TileY);
			else
				DrawTile(lTile.GridX, lTile.GridY, lTile.TileX, lTile.TileY, hdc, rect);
		}		
		tilemap.DeleteObject();
	}
}

void TileManager::DrawTile(int screenColX, int screenColY, int tileColX, int tileColY, HDC hdc, RECT rect)
{
	int tileWidth = 32;
	int tileHeight = 32;
	HDC hTileDC = CreateCompatibleDC(hdc);
	FillRect(hTileDC, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	SelectObject(hTileDC, tileset);
	BitBlt(hdc, screenColX * tileWidth, screenColY * tileHeight, tileWidth, tileHeight, hTileDC, tileColX * tileWidth, tileColY * tileHeight, SRCCOPY);	
	DeleteDC(hTileDC);
}