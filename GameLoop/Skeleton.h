#ifndef Skeleton_H
#define Skeleton_H

#include "Win.h"

class CSkeleton : public CWin
{
private:
	int width;
	int height;
	RECT rect;
	HDC bufDC;
	HBITMAP bufBMP;
	HANDLE hImage;
	HANDLE hImage2;
public:
	CSkeleton();
	~CSkeleton();

	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);

	void GameInit();
	void GameLoop(HWND);
	void GameEnd();
};

#endif
