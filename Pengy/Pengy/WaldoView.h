#pragma once
#include "view.h"
#include "Bitmap.h"
using namespace dotnetguy;

class Waldo;

class WaldoView : public View
{
private:
	Waldo * pWaldo;
	HANDLE pBitmap;
	HANDLE pMask;
	int* width_height;
public:
	WaldoView(Waldo * pWaldo);
	~WaldoView(void);
	void Draw(HDC hDC, RECT rect, int xFrom, int xTo);
};
