#include "Renderer.h"
#include "Location.h"

bool Renderer::ShowFps = true;
bool Renderer::ShowDebug = false;
bool Renderer::ShowSurfaces = false;

Renderer* Renderer::pInstance = NULL;

Renderer* Renderer::Inst(){
  if(pInstance == NULL){
    pInstance = new Renderer();
  }
  return pInstance;
}

Renderer::Renderer()
{
	bitmap.LoadDIBFile("res/background.bmp");
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
    for (unsigned int i= 0; i< myViews.size(); i++)
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
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.bottom = 800;
	rect.right = 800;
	bitmap.PaintDIB(hdc, &rect, NULL);
	int xFrom = characterX - 400;
	if(xFrom < 0) xFrom = 0;
	int xTo = xFrom + 800;
	if(xTo >= levelLength)
	{
		xTo = levelLength;
		xFrom = levelLength - 800;
	}
	if(numViews > 0)
	{
		vector<View*>::iterator iterator = myViews.begin();
		while(iterator!=myViews.end())
		{
			View * view = *iterator;
			view->Draw(hdc, rect, xFrom, xTo);
			iterator++;
		}
	}
}

void Renderer::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	Location * from;
	Location * to;

	switch(message)
	{
	case CM_LEVEL_LENGTH:
		levelLength = (int)wParam;
		break;
	case CM_CHARACTER_MOVE_X_FROM_TO:
		from = (Location*)wParam;
		to = (Location*)lParam;
		characterX = (int)to->X;

		break;
	case CM_CHARACTER_FALL_Y_FROM_TO:
		from = (Location*)wParam;
		to = (Location*)lParam;
		characterX = (int)to->X;

		break;
	case CM_CHARACTER_JUMP_Y_FROM_TO:
		from = (Location*)wParam;
		to = (Location*)lParam;
		characterX = (int)to->X;

		break;
	}
}