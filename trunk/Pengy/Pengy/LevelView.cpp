#include "LevelView.h"

vector<Tile*>* LevelView::myTiles = NULL;
HANDLE LevelView::tilemap = NULL;

LevelView::LevelView(){ 
	if(myTiles == NULL)
		myTiles = new vector<Tile *>();
	registerToGraphics();
}

LevelView::~LevelView(){
	unRegisterToGraphics();
}

void LevelView::Draw(HDC hDC, HWND m_hWnd)
{
	RECT rect;
	::GetClientRect(m_hWnd, &rect);

	// iterate trew all tiles
	vector<Tile*>::iterator iterator = myTiles->begin();
	while(iterator!=myTiles->end())
	{
		Tile * tile = *iterator;
		
		// draw the tile non-transparent
		DrawTile(tile, hDC, rect);
		iterator++;
	}
}

void LevelView::SetTiles(vector<Tile> tiles, LPCSTR path)
{
	vector<Tile>::iterator iterator = tiles.begin();
	if(myTiles == NULL)
		myTiles = new vector<Tile *>();

	while(iterator!=tiles.end())
	{
		Tile tile = *iterator;
		myTiles->push_back(new Tile(tile.GridX, tile.GridY, tile.TileX, tile.TileY, tile.Transparant));

		iterator++;
	}
	tilemap = LoadImage(NULL, path, IMAGE_BITMAP, 0, 0,LR_LOADFROMFILE);
}

void LevelView::DrawTile(Tile * tile, HDC hdc, RECT rect)
{
	DrawTile(tile, hdc, rect, 0, 0);
}

void LevelView::DrawTile(Tile * tile, HDC hdc, RECT rect, int offsetX)
{
	DrawTile(tile, hdc, rect, offsetX, 0);
}

void LevelView::DrawTile(Tile * tile, HDC hdc, RECT rect, int offsetX, int offsetY)
{
	HDC hTileDC = CreateCompatibleDC(hdc);
	FillRect(hTileDC, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	SelectObject(hTileDC, tilemap);
	BitBlt(hdc, (tile->GridX * tile->TileWidth) + offsetX, (tile->GridY * tile->TileHeight) + offsetY, tile->TileWidth, tile->TileHeight, hTileDC, tile->TileX * tile->TileWidth, tile->TileY * tile->TileHeight, SRCCOPY);	
	DeleteDC(hTileDC);
}