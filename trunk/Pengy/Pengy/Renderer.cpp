#include "Renderer.h"
#include "Location.h"

bool Renderer::ShowFps = true;
bool Renderer::ShowDebug = false;
bool Renderer::ShowSurfaces = false;

Renderer* Renderer::pInstance = NULL;

Renderer* Renderer::Instance(){
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

void Renderer::Attach( View *pView)
{
    myViews.push_back( pView);
	numViews++;
}

void Renderer::Detach( View *myView)
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

void Renderer::Render(HDC hdc) 
{
	HBRUSH backBrush;
	backBrush = CreateSolidBrush(RGB(171, 207, 236));

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.bottom = 600;
	rect.right = 800;
	
	FillRect(hdc, &rect, backBrush);

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
			View * pView = *iterator;
			pView->Draw(hdc, rect, xFrom, xTo);
			iterator++;
		}
	}

	DeleteObject(backBrush);
}

void Renderer::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	Location * pFrom;
	Location * pTo;

	switch(message)
	{
	case CM_LEVEL_LENGTH:
		levelLength = (int)wParam;
		break;
	case CM_CHARACTER_MOVE_X_FROM_TO:
		pFrom = (Location*)wParam;
		pTo = (Location*)lParam;
		characterX = (int)pTo->X;

		break;
	case CM_CHARACTER_FALL_Y_FROM_TO:
		pFrom = (Location*)wParam;
		pTo = (Location*)lParam;
		characterX = (int)pTo->X;

		break;
	case CM_CHARACTER_JUMP_Y_FROM_TO:
		pFrom = (Location*)wParam;
		pTo = (Location*)lParam;
		characterX = (int)pTo->X;

		break;
	}
}