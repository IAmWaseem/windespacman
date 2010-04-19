#include "MenuView.h"

MenuView::MenuView(void)
{
	image = LoadImage(NULL, "res/menu.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

MenuView::~MenuView(void)
{
}

void MenuView::Draw(HDC hdc, RECT rect, int xFrom, int xTo)
{
	HDC bufDC = CreateCompatibleDC(hdc);
	SelectObject(bufDC, image);

	BitBlt(hdc, 0, 0, 1014, 671, bufDC, 0, 0, SRCCOPY);	
	DeleteDC(bufDC);
}
