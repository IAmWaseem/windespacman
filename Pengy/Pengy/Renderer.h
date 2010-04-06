#pragma once

#include <windows.h>
#include <vector>
#include "View.h"
#include <iostream>
#include "Bitmap.h"
#include "Observer.h"
using namespace std;
using namespace dotnetguy;

class View;

class Renderer : public Observer
{
public:
    static Renderer* Instance();
    ~Renderer();

	void Attach(View *pView);
	void Detach(View *pView);
	void DetachAll();
	void Render(HDC hdc);
	void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);

	static bool ShowDebug;
	static bool ShowFps;
	static bool ShowSurfaces;
  protected:
    Renderer();
  private:
    Bitmap bitmap;
    static Renderer* pInstance;
	vector<View*> myViews;
	int numViews;
	int levelLength;
	int characterX;
	bool singleRender;
	bool drawUntop;
	View * singleView;
	View * untopView;
};