#pragma once
#include "view.h"
#include "Bitmap.h"
using namespace dotnetguy;

class MisterFrost;

class MisterFrostView : public View
{
private:
	MisterFrost * pMisterFrost;
	HANDLE pBitmapLeft;
	HANDLE pMaskLeft;
	HANDLE pBitmapRight;
	HANDLE pMaskRight;
	int* width_height;
public:
	MisterFrostView(MisterFrost * pMisterFrost);
	~MisterFrostView(void);
	void Draw(HDC hDC, RECT rect, int yFrom, int yTo);
};
