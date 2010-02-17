#include "Renderer.h"


Renderer* Renderer::pInstance = NULL;

Renderer* Renderer::Inst(){
  if(pInstance == NULL){
    pInstance = new Renderer();
  }
  return pInstance;
}

Renderer::Renderer()
{
	bitmap.LoadDIBFile("res/PengyAutumnLeft2.bmp");
	numViews = 0;
}

Renderer::~Renderer(){
  if(pInstance != 0)delete pInstance;
}

void Renderer::attach( View *myView)
{
    myViews.push_back( myView);
	numViews++;
}

void Renderer::detach( View *myView)
{
    for (int i= 0; i< myViews.size(); i++)
    {
        if (myViews[i]== myView)
        {
            myViews.erase(myViews.begin()+i);
			numViews--;
            return;
        }
    }
}

void Renderer::render(HDC hdc)
{
	if(numViews > 0)
	{
		vector<View*>::iterator iterator = myViews.begin();
		while(iterator!=myViews.end())
		{
			View * view = *iterator;
			view->Draw(hdc);
			iterator++;
		}
	}
	RECT placeRect;
	placeRect.left = 0;
	placeRect.top = 0;
	placeRect.right = 0+ 101;
	placeRect.bottom = 0 + 134;	
	bitmap.TransparentPaint(hdc, RGB(46, 46, 46), &placeRect, NULL);
}
