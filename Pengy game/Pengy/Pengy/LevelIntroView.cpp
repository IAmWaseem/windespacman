#include "LevelIntroView.h"

LevelIntroView::LevelIntroView(LPCSTR pictureA, LPCSTR pictureB) : View()
{
	bitmapA = LoadImage(NULL, pictureA, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bitmapB = LoadImage(NULL, pictureB, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	currentBitmap = bitmapA;
}

LevelIntroView::~LevelIntroView(void)
{
}

void LevelIntroView::NextPicture()
{
	currentBitmap = bitmapB;
}

void LevelIntroView::Draw(HDC hdc, RECT rect, int xFrom, int xTo)
{
	HDC bufDC = CreateCompatibleDC(hdc);
	SelectObject(bufDC, currentBitmap);

	BitBlt(hdc, 0, 0, 1014, 671, bufDC, 0, 0, SRCCOPY);	
	DeleteDC(bufDC);
}
