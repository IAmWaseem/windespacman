#pragma once

#include <windows.h>
#include <vector>
using namespace std;

class View;

class Renderer
{
public:
    static Renderer* Inst();
    ~Renderer();

	void attach(View *myView);
	void detach(View *myView);
	void render(HDC hdc);

  protected:
    Renderer();
  private:
    static Renderer* pInstance;
	vector <View*> myViews;
};