#include "LevelView.h"

LevelView::LevelView(){ 
	registerToGraphics();
}

LevelView::~LevelView(){
	unRegisterToGraphics();
}

void LevelView::Draw(HDC hDC, HWND m_hWnd)
{

	HDC hImageDC = CreateCompatibleDC(hDC);
	RECT rect;
	::GetClientRect(m_hWnd, &rect);
	FillRect(hImageDC, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	SelectObject(hImageDC, tilemap);

	int tileWidth = 32;
	vector<Tile*>::iterator iterator = myTiles.begin();
	while(iterator!=myTiles.end())
	{
		Tile * tile = *iterator;

		BitBlt(hDC, 0,0, tileWidth, tileWidth, hImageDC, 0,0, SRCCOPY);
		iterator++;
	}
}

void LevelView::SetTiles(vector<Tile*> tiles, LPCSTR path)
{
	myTiles = tiles;
	tilemap = LoadImage(NULL, path, IMAGE_BITMAP, 0, 0,LR_LOADFROMFILE);
}