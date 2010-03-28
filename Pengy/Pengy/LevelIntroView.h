#pragma once
#include "view.h"

class LevelIntroView : public View
{
public:
	LevelIntroView(LPCSTR pictureA, LPCSTR pictureB);
	~LevelIntroView(void);
	void NextPicture();
	void Draw(HDC hdc, RECT rect, int xFrom, int xTo);
private:
	HANDLE bitmapA;
	HANDLE bitmapB;
	HANDLE currentBitmap;
};
