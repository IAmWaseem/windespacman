#pragma once

#include <windows.h>
#include "messages.h"
#include <string>
using namespace std;

class Renderer;

class View
{
public:
    View();
    void registerToGraphics();
	void unRegisterToGraphics();
	virtual void Draw(HDC hdc, RECT rect, int xFrom, int xTo) = 0;
	void BitBltTransparant(HDC hdc, int x, int y, int cx, int cy, HDC source, int x1, int y1, HANDLE image, HANDLE transparantMask);
	HANDLE CreateBitmapMask(HANDLE hbmColour, COLORREF crTransparent, int width, int height);
    ~View();
private:
	
	Renderer* renderer;
};
