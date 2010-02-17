#ifndef Skeleton_H
#define Skeleton_H

#include "Win.h"
#include "Bitmap.h"
#include "Renderer.h"
#include "Character.h"
#include <sstream>
using namespace dotnetguy;

class CSkeleton : public CWin
{
public:
	CSkeleton();
	~CSkeleton();

	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	void GameInit();
	void GameLoop(HWND);
	void GameEnd();
private:
	Character* character;
	Renderer* renderer;
	MessageQueue* messageQueue;
	Level* level;
	void Update();
	void Render(HWND);
	SYSTEMTIME st;
	Bitmap bitmap;
	HDC graphics;
	HDC bufDC;
};

#endif
