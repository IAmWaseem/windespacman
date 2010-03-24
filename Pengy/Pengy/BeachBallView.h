#pragma once
#include "view.h"
#include "Bitmap.h"
using namespace dotnetguy;

class BeachBall;

class BeachBallView : public View
{
private:
	BeachBall * pBeachBall;
	HANDLE pBitmapLeft;
	HANDLE pMaskLeft;
	HANDLE pBitmapRight;
	HANDLE pMaskRight;
	int* width_height;
public:
	BeachBallView(BeachBall * pBeachBall);
	~BeachBallView(void);
	void Draw(HDC hDC, RECT rect, int xFrom, int xTo);
};
