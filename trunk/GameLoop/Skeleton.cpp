#include "Skeleton.h"
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

