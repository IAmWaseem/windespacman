#include "LevelView.h"

vector<Tile*>* LevelView::myTiles = NULL;
vector<Surface*>* LevelView::surfaces = NULL;
HANDLE LevelView::tilemap = NULL;
LPCSTR LevelView::tilemapPath = "";
int LevelView::tilemapWidth = 4096;
int LevelView::tilemapHeight = 1024;
HANDLE LevelView::myMask = NULL;

LevelView::LevelView(){ 
	if(myTiles == NULL)
		myTiles = new vector<Tile *>();
	RegisterToGraphics();
}

LevelView::~LevelView(){
	UnRegisterToGraphics();
}

void LevelView::Draw(HDC hDC, RECT rect, int xFrom, int xTo)
{
	if(!pWorld->Instance()->menu)
	{
		if(myTiles != NULL)
		{
			// iterate trew all tiles
			vector<Tile*>::iterator iterator = myTiles->begin();
			while(iterator!=myTiles->end())
			{
				Tile * tile = *iterator;
				if(ShouldDrawTile(tile, xFrom, xTo))
					DrawTile(tile, hDC, rect, -1 * xFrom);
				iterator++;
			}
		}

#pragma region surfaces
		if(Renderer::ShowSurfaces)
		{
			vector<Surface*> tempList;
			if(surfaces != NULL)
			{
				vector<Surface*>::iterator surfIterator = surfaces->begin();
				while(surfIterator != surfaces->end())
				{
					Surface * surf = *surfIterator;
					tempList.push_back(surf);
					surfIterator++;
				}
			}
			
			HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 25, 5));
			HPEN cloud = CreatePen(PS_DOT, 1, RGB(255, 25, 5));
			SelectObject(hDC, hPen);

			vector<Surface*>::iterator surfIterator = tempList.begin();
			while(surfIterator != tempList.end())
			{				
				Surface * surface = *surfIterator;

				if(surface->isCloud)
					SelectObject(hDC, cloud);
				else
					SelectObject(hDC, hPen);

				if(surface->isSlope!=0)
				{
					if (surface->isSlope==1)
					{
						MoveToEx(hDC,surface->xFrom - xFrom, surface->yFrom,NULL);
						LineTo(hDC,surface->xTo - xFrom, surface->yFrom + (surface->yTo - surface->yFrom));
					}
					else
					{
						MoveToEx(hDC,surface->xFrom - xFrom, surface->yTo,NULL);
						LineTo(hDC,surface->xTo - xFrom, surface->yTo+ (surface->yFrom - surface->yTo));
					}
				}
				else
					Rectangle(hDC, surface->xFrom - xFrom, surface->yFrom, surface->xTo - xFrom, surface->yFrom + (surface->yTo - surface->yFrom));
				
				surfIterator++;
			}
			DeleteObject(hPen);
			DeleteObject(cloud);		
		}
#pragma endregion

#pragma region fps
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
#pragma endregion

	}
}

void LevelView::SetSurface(vector<Surface*> * theSurface)
{
	vector<Surface*>::iterator iterator = theSurface->begin();

	//if(surfaces == NULL)
		surfaces = new vector<Surface *>();

	while(iterator != theSurface->end())
	{
		Surface * surf = *iterator;

		surfaces->push_back(surf);

		iterator++;
	}
}

void LevelView::SetTiles(vector<Tile> tiles, LPCSTR path)
{
	tilemapPath = path;
	vector<Tile>::iterator iterator = tiles.begin();
	//if(myTiles == NULL)
		myTiles = new vector<Tile *>();

	while(iterator!=tiles.end())
	{
		Tile tile = *iterator;
		myTiles->push_back(new Tile(tile.GridX, tile.GridY, tile.TileX, tile.TileY, tile.Transparant, tile.Depth));

		iterator++;
	}
	tilemap = LoadImage(NULL, tilemapPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
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

	if(tilemap == NULL)
	{
		ReimportTilemap();
	}
	SelectObject(hTileDC, tilemap);

	if(tile->Transparant == true)
	{	
		BitBltTransparant(hdc, (tile->GridX * tile->TileWidth()) + (offsetX / tile->DepthFactor()), (tile->GridY * tile->TileHeight()) + offsetY, tile->TileWidth(), tile->TileHeight(), hTileDC, tile->TileX * tile->TileWidth(), tile->TileY * tile->TileHeight(), tilemap, myMask);
	}
	else
	{
		BitBlt(hdc, (tile->GridX * tile->TileWidth()) + (offsetX / tile->DepthFactor()), (tile->GridY * tile->TileHeight()) + offsetY, tile->TileWidth(), tile->TileHeight(), hTileDC, tile->TileX * tile->TileWidth(), tile->TileY * tile->TileHeight(), SRCCOPY);	
	}

	DeleteDC(hTileDC);
}

void LevelView::ReimportTilemap()
{
	DeleteObject(tilemap);
	DeleteObject(myMask);

	if(strlen(tilemapPath) > 0)
	{
		tilemap = LoadImage(NULL, tilemapPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		myMask = CreateBitmapMask(tilemap, RGB(0,0,0), tilemapWidth, tilemapHeight);
	}
}

void LevelView::StartGame()
{
	DeleteObject(tilemap);
	DeleteObject(myMask);

	if(myTiles != NULL)
	{
		Tile * pTile;
		vector<Tile*>::iterator iterator = myTiles->begin();
		while(iterator != myTiles->end())
		{
			pTile = *iterator;
			delete pTile;
			iterator++;
		}
		myTiles->clear();
	}

	if(surfaces != NULL)
	{
		Surface * pSurface;
		vector<Surface*>::iterator it = surfaces->begin();
		while(it != surfaces->end())
		{
			pSurface = *it;
			pSurface = NULL;
			it++;
		}
		surfaces->clear();
	}

	if(strlen(tilemapPath) > 0)
	{
		tilemap = LoadImage(NULL, tilemapPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		myMask = CreateBitmapMask(tilemap, RGB(0,0,0), tilemapWidth, tilemapHeight);
	}
}

bool LevelView::ShouldDrawTile(Tile * tile, int xFrom, int xTo)
{
	float xPos = (tile->GridX * tile->TileWidth()) + ( -xFrom / tile->DepthFactor());
	int screenWidth = xTo - xFrom;
	if(xPos + tile->TileWidth() >= 0 && xPos <= screenWidth)
		return true;
	return false;
}