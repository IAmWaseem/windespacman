#pragma once
#include "view.h"
#include "Bitmap.h"
using namespace dotnetguy;

class Waldo;

class WaldoView : public View
{
private:
	Waldo * pWaldo;
	Bitmap * pBitmap;
public:
	WaldoView(Waldo * pWaldo);
	~WaldoView(void);
	void Draw(HDC hDC, int xFrom, int xTo);
};
