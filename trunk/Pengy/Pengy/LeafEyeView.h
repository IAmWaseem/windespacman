#pragma once
#include "view.h"
#include "Bitmap.h"
using namespace dotnetguy;

class LeafEye;

class LeafEyeView : public View
{
private:
	LeafEye * pLeafEye;
	HANDLE pBitmapLeft;
	HANDLE pMaskLeft;
	HANDLE pBitmapRight;
	HANDLE pMaskRight;
	int* width_height;
public:
	LeafEyeView(LeafEye * pLeafEye);
	~LeafEyeView(void);
	void Draw(HDC hDC, RECT rect, int yFrom, int yTo);
};
