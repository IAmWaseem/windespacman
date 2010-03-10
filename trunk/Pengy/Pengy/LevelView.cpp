#include "LevelView.h"

vector<Tile*>* LevelView::myTiles = NULL;
vector<Surface*>* LevelView::surfaces = NULL;
HANDLE LevelView::tilemap = NULL;
int LevelView::tilemapWidth = 2048;
int LevelView::tilemapHeight = 2048;
HANDLE LevelView::myMask = NULL;

LevelView::LevelView(){ 
	if(myTiles == NULL)
		myTiles = new vector<Tile *>();
	registerToGraphics();
}

LevelView::~LevelView(){
	unRegisterToGraphics();
}

void LevelView::Draw(HDC hDC, RECT rect, int xFrom, int xTo)
{
	if(myTiles != NULL)
	{
		// iterate trew all tiles
		vector<Tile*>::iterator iterator = myTiles->begin();
		while(iterator!=myTiles->end())
		{
			Tile * tile = *iterator;

			// draw the tile non-transparent
			DrawTile(tile, hDC, rect, -1*xFrom);
			iterator++;
		}
	}
	
	if(surfaces != NULL && Renderer::ShowSurfaces)
	{
		HPEN hPen = CreatePen(PS_DASHDOTDOT, 1, RGB(255, 25, 5));
		SelectObject(hDC, hPen);

		vector<Surface*>::iterator surfIterator = surfaces->begin();
		while(surfIterator != surfaces->end())
		{
			Surface * surface = *surfIterator;
			Rectangle(hDC, surface->xFrom - xFrom, surface->yFrom, surface->xTo - xFrom, surface->yFrom + (surface->yTo - surface->yFrom));
			surfIterator++;
		}
		DeleteObject(hPen);
	}
	
	if(Renderer::ShowFps)
	{
		SYSTEMTIME now;
		GetSystemTime(&now);
		
		int difInSec = now.wSecond - st.wSecond;
		int difInMSec = now.wMilliseconds - st.wMilliseconds;
		int ms1 = now.wMilliseconds;
		
		if(difInSec != 0)
			difInMSec = difInMSec + 1000;

		ostringstream s;
		s << "FPS: ";
		if(difInMSec == 0)
			s << "1000+";
		else
		{
			float temp_fps = (float)(1000 / difInMSec);
			int temp2_fps = (int)temp_fps;
			s << (temp2_fps);
		}

		// cast to c_string
		LPCSTR fps = "";
		string temp; 
		temp = s.str();
		fps = temp.c_str();

		
		if(st.wSecond == now.wSecond)
			TextOut(hDC, 15, 15, fps, strlen(fps));
		else
			TextOut(hDC, 15, 15, "FPS:", strlen("FPS:"));

		// set the time of the last update to this
		st = now;
	}
}

void LevelView::SetSurface(vector<Surface*> * theSurface)
{
	vector<Surface*>::iterator iterator = theSurface->begin();

	if(surfaces == NULL)
		surfaces = new vector<Surface *>();

	while(iterator!=theSurface->end())
	{
		Surface * surf = *iterator;

		surfaces->push_back(surf);

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
		myTiles->push_back(new Tile(tile.GridX, tile.GridY, tile.TileX, tile.TileY, tile.Transparant, tile.Depth));

		iterator++;
	}
	tilemap = LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	myMask = CreateBitmapMask(tilemap, RGB(0,0,0), tilemapWidth, tilemapHeight);
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
	//FillRect(hTileDC, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	float depthFactor = 1;

	if(tile->Depth == 0)
		depthFactor = 1.00f;
	else if(tile->Depth == 1)
		depthFactor = 1.20f;
	else if(tile->Depth == 2)
		depthFactor = 1.50f;
	else if(tile->Depth == 3)
		depthFactor = 4.00f;

	SelectObject(hTileDC, tilemap);

	if(tile->Transparant == true)
	{	
		BitBltTransparant(hdc, (tile->GridX * tile->TileWidth()) + (offsetX / depthFactor), (tile->GridY * tile->TileHeight()) + offsetY, tile->TileWidth(), tile->TileHeight(), hTileDC, tile->TileX * tile->TileWidth(), tile->TileY * tile->TileHeight(), tilemap, myMask);
	}
	else
	{
		BitBlt(hdc, (tile->GridX * tile->TileWidth()) + (offsetX / depthFactor), (tile->GridY * tile->TileHeight()) + offsetY, tile->TileWidth(), tile->TileHeight(), hTileDC, tile->TileX * tile->TileWidth(), tile->TileY * tile->TileHeight(), SRCCOPY);	
	}

	DeleteDC(hTileDC);
}