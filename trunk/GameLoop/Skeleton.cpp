#include "Skeleton.h"
#include "Bitmap.h"

using namespace dotnetguy;
/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////
CSkeleton::CSkeleton()
{
}

CSkeleton::~CSkeleton()
{
}

void CSkeleton::GameInit()
{
	width = 400;
	height = 300;

	char picfile[] = "res/Penguin.bmp";
	hImage = LoadImage(NULL, picfile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	char picfile2[] = "res/Penguin2.bmp";
	hImage2 = LoadImage(NULL, picfile2, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	char picfile3[] = "res/Penguin3.bmp";
	hImage3 = LoadImage(NULL, picfile3, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	char picfile4[] = "res/Penguin4.bmp";
	hImage4 = LoadImage(NULL, picfile4, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	char tilesetplace[] = "res/Woodland_Tileset.bmp";
	tileset = LoadImage(NULL, tilesetplace, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	
	::GetClientRect(m_hWnd, &rect);
	bufDC = CreateCompatibleDC(graphics);
	bufBMP = CreateCompatibleBitmap(graphics, rect.right, rect.bottom);
	SelectObject(bufDC, bufBMP);
	::FillRect(bufDC, &rect, ::CreateSolidBrush(0x00FFFFFF));
}

void CSkeleton::GameLoop(HWND hWnd)
{		
	BITMAP bitmap;
	SIZE imgSize;
	RECT rect;
	if(pinguin == 1)
	{
		if(direction==0){
			GetObject(hImage2, sizeof(BITMAP), &bitmap);
		}
		else
		{
			GetObject(hImage4, sizeof(BITMAP), &bitmap);
		}
	}
	else
	{	
		if(direction==0){
			GetObject(hImage, sizeof(BITMAP), &bitmap);
		}
		else
		{
			GetObject(hImage3, sizeof(BITMAP), &bitmap);
		}
	}

	imgSize.cx = bitmap.bmWidth;
	imgSize.cy = bitmap.bmHeight;

	HDC hImageDC = CreateCompatibleDC(bufDC);
	

	::GetClientRect(m_hWnd, &rect);
	FillRect(bufDC, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	FillRect(hImageDC, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	

	if(pinguin == 1)
	{
		if(direction==0){
			SelectObject(hImageDC, hImage2);
		}
		else
		{
			SelectObject(hImageDC, hImage4);
		}
	}
	else
	{	
		if(direction==0){
			SelectObject(hImageDC, hImage);
		}
		else
		{
			SelectObject(hImageDC, hImage3);
		}
	}
	
	


	if(jump){
	if (jump<756)
	{
		if(jump%18==0)
		{
		this->positionY+=jump_speed;
		jump_speed+=gravity;
		}
		jump++;
	}else{jump=0;jump_speed=-20;}}
	
	RECT placeRect;
	placeRect.left = positionX;
	placeRect.top = positionY;
	placeRect.right = positionX+80;
	placeRect.bottom = positionY + 111;
	
	/*DrawTile(0, 0, 3, 0, bufDC, hWnd);
	DrawTile(1, 0, 4, 0, bufDC, hWnd);
	DrawTile(2, 0, 5, 0, bufDC, hWnd);

	DrawTile(0, 1, 3, 1, bufDC, hWnd);
	DrawTile(1, 1, 4, 1, bufDC, hWnd);
	DrawTile(2, 1, 5, 1, bufDC, hWnd);

	DrawTile(1, 2, 4, 2, bufDC, hWnd);
	
	DrawTile(1, 3, 4, 2, bufDC, hWnd);

	DrawTile(0, 4, 0, 0, bufDC, hWnd);
	DrawTile(1, 4, 4, 3, bufDC, hWnd);
	DrawTile(2, 4, 0, 0, bufDC, hWnd);

	DrawTile(0, 5, 0, 0, bufDC, hWnd);
	DrawTile(1, 5, 0, 0, bufDC, hWnd);
	DrawTile(2, 5, 0, 0, bufDC, hWnd);*/

	Bitmap tiles;
	tiles.LoadDIBFile("res/Woodland_Tileset.bmp");
tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 0, 0, 0, 0);
	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 1, 0, 0, 0);
	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 2, 0, 0, 0);

	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 0, 0, 3, 0);
	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 1, 0, 4, 0);
	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 2, 0, 5, 0);

	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 0, 1, 13, 13);
	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 1, 1, 0,0);
	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 2, 1, 15, 13);

	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 0, 1, 3, 1);
	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 1, 1, 4, 1);
	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 2, 1, 5, 1);

	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 0, 2, 13, 14);
	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 1, 2, 14, 14);
	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 2, 2, 15, 14);

	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 0, 2, 15, 12);
	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 1, 2, 4, 2);
	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 2, 2, 15, 12);
	
	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 0, 3, 13, 15);
	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 1, 3, 14, 15);
	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 2, 3, 15, 15);

	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 0, 3, 15, 12);	
	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 1, 3, 4, 2);	
	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 2, 3, 15, 12);

	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 0, 4, 0, 0);
	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 1, 4, 4, 3);
	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 2, 4, 0, 0);

	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 0, 5, 0, 0);
	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 1, 5, 0, 0);
	tiles.TransparentPaintTile(bufDC, RGB(0, 0, 0), 2, 5, 0, 0);

	Bitmap bitmap2;
	bitmap2.LoadDIBFile("res/p1.bmp");
	bitmap2.TransparentPaint(bufDC, RGB(255, 255, 0), &placeRect, NULL);

	BitBlt(bufDC, 300 + positionX, 50 + positionY ,imgSize.cx, imgSize.cy, hImageDC, 0, 0, SRCCOPY);
	ReleaseDC(hWnd, hImageDC);
	DeleteDC(hImageDC);
	BitBlt(graphics, 
		rect.left,rect.top, rect.right, rect.bottom,
		bufDC, 0, 0, SRCCOPY);

	ReleaseDC(hWnd, bufDC);
}

void CSkeleton::DrawTile(int screenColX, int screenColY, int tileColX, int tileColY, HDC hdc, HWND hWnd)
{
	//int tileWidth = 32;
	//int tileHeight = 32;
	//HDC hTileDC = CreateCompatibleDC(hdc);
	//FillRect(hTileDC, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	//SelectObject(hTileDC, tileset);
	//BitBlt(hdc, screenColX * tileWidth, screenColY * tileHeight, tileWidth, tileHeight, hTileDC, tileColX * tileWidth, tileColY * tileHeight, SRCCOPY);	
	//ReleaseDC(hWnd, hTileDC);
	//DeleteDC(hTileDC);
}

void CSkeleton::GameEnd()
{
}

/////////////////////////////////////
// Member functions                  //
/////////////////////////////////////

LRESULT CSkeleton::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return CWin::MsgProc(hWnd, uMsg, wParam, lParam);
}

