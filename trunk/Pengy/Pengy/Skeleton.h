#ifndef Skeleton_H
#define Skeleton_H

#include "Win.h"
#include "Bitmap.h"
#include "Renderer.h"
#include "Character.h"
#include "SurfaceLevel.h"
#include <sstream>
using namespace dotnetguy;

class CSkeleton : public CWin
{
public:
	CSkeleton();
	~CSkeleton();

	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	void GameInit();
	void GameLoop();
	void GameEnd();
private:
	Character* character;
	Renderer* renderer;
	MessageQueue* messageQueue;
	SurfaceLevel* level;
	void Update();
	void Render(HWND);
	HDC bufDC;
	ULONGLONG previousUpdateTime;
};

#endif
