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
	HANDLE tileset;
	HANDLE hImage;
	HANDLE hImage2;
	HANDLE hImage3;
	HANDLE hImage4;
public:
	CSkeleton();
	~CSkeleton();
	
	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	void DrawTile(int screenColX, int screenColY, int tileColX, int tileColY, HDC hdc, HWND hWnd);
	void GameInit();
	void GameLoop(HWND);
	void GameEnd();
};

#endif
