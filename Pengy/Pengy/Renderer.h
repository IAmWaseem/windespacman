#pragma once

#include <windows.h>
#include <vector>
#include "View.h"
#include <iostream>
#include "Bitmap.h"
using namespace std;
using namespace dotnetguy;

class View;

class Renderer
{
public:
    static Renderer* Inst();
    ~Renderer();

	void attach(View *myView);
	void detach(View *myView);
	void render(HDC hdc, HWND m_hWnd);

  protected:
    Renderer();
  private:
    Bitmap bitmap;
    static Renderer* pInstance;
	vector<View*> myViews;
	int numViews;
};