#include "Skeleton.h"
#include "Bitmap.h"
#include <sstream>
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
	GetSystemTime(&st);
	width = 400;
	height = 300;
	char picfile[] = "res/Penguin.bmp";
	hImage = LoadImage(NULL, picfile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	bitmap2.LoadDIBFile("res/p1.bmp");
	bitmap3.LoadDIBFile("res/Summer.bmp");

	char picfile2[] = "res/Penguin2.bmp";
	hImage2 = LoadImage(NULL, picfile2, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	char picfile3[] = "res/Penguin3.bmp";
	hImage3 = LoadImage(NULL, picfile3, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	char picfile4[] = "res/Penguin4.bmp";
	hImage4 = LoadImage(NULL, picfile4, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	tm = TileManager("res/Woodland_Tileset.bmp");
	tm.ClearTiles();	
	tm.AddTile(0, 0, 0, 0);
	tm.AddTile(1, 0, 0, 0);
	tm.AddTile(2, 0, 0, 0);
	tm.AddTile(0, 0, 3, 0, true);
	tm.AddTile(1, 0, 4, 0, true);
	tm.AddTile(2, 0, 5, 0, true);
	tm.AddTile(Tile(0, 1, 13, 13));
	tm.AddTile(Tile(1, 1, 0, 0));
	tm.AddTile(Tile(2, 1, 15, 13));
	tm.AddTile(Tile(0, 1, 3, 1, true));
	tm.AddTile(Tile(1, 1, 4, 1, true));
	tm.AddTile(Tile(2, 1, 5, 1, true));
	tm.AddTile(Tile(0, 2, 13, 14));
	tm.AddTile(Tile(1, 2, 14, 14));
	tm.AddTile(Tile(2, 2, 15, 14));
	tm.AddTile(Tile(0, 2, 15, 12, true));
	tm.AddTile(Tile(1, 2, 4, 2, true));
	tm.AddTile(Tile(2, 2, 15, 12, true));
	tm.AddTile(Tile(0, 3, 13, 15));
	tm.AddTile(Tile(1, 3, 14, 15));
	tm.AddTile(Tile(2, 3, 15, 15));
	tm.AddTile(Tile(0, 3, 15, 12, true));
	tm.AddTile(Tile(1, 3, 4, 2, true));
	tm.AddTile(Tile(2, 3, 15, 12, true));
	tm.AddTile(Tile(0, 4, 0, 0));
	tm.AddTile(Tile(1, 4, 4, 3));
	tm.AddTile(Tile(2, 4, 0, 0));
	tm.AddTile(Tile(0, 5, 0, 0));
	tm.AddTile(Tile(1, 5, 0, 0));
	tm.AddTile(Tile(2, 5, 0, 0));

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


	SYSTEMTIME now;
	GetSystemTime(&now);

	float fps1 = st.wMilliseconds;
	float fps2 = now.wMilliseconds;
	float dif = 0;

	if(fps1 > fps2)
		fps2 += 1000;

	dif = fps2 - fps1;

	float cur_fps = 1000 / dif;

	ostringstream s;
	s << "FPS: ";
	if(cur_fps < 1000)
		s << " ";
	if(cur_fps < 100)
		s << " ";
	if(cur_fps < 10)
		s << " ";


	s << cur_fps;
	LPCSTR fps = "";
	string temp;
	temp = s.str();
	fps = temp.c_str();

	GetSystemTime(&st);

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
		if (jump<198)
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
	tm.RenderTiles(bufDC, rect);

	bitmap2.TransparentPaint(bufDC, RGB(255, 255, 0), &placeRect, NULL);
	//bitmap3.TransparentPaint(bufDC, RGB(0, 255, 0), NULL, NULL);
	TextOut(bufDC, 10,550, fps, 20);

	BitBlt(bufDC, 300 + positionX, 50 + positionY ,imgSize.cx, imgSize.cy, hImageDC, 0, 0, SRCCOPY);
	ReleaseDC(hWnd, hImageDC);
	DeleteDC(hImageDC);
	BitBlt(graphics, 
		rect.left,rect.top, rect.right, rect.bottom,
		bufDC, 0, 0, SRCCOPY);

	ReleaseDC(hWnd, bufDC);
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

