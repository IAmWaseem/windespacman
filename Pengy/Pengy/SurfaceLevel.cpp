#include "SurfaceLevel.h"
#include "Location.h"

SurfaceLevel* SurfaceLevel::pInstance = NULL;

SurfaceLevel* SurfaceLevel::Inst(){
  if(pInstance == NULL){
    pInstance = new SurfaceLevel();
  }
  return pInstance;
}

SurfaceLevel::SurfaceLevel(){ 
	surfaces = new vector<Surface*>();

	Surface * surface1 = new Surface();
	surface1->xFrom = 0;
	surface1->yFrom = 483;
	surface1->xTo = 367;
	surface1->yTo = 483;

	Surface * surface2 = new Surface();
	surface2->xFrom = 586;
	surface2->yFrom = 483;
	surface2->xTo = 800;
	surface2->yTo = 483;

	Surface * surface3 = new Surface();
	surface3->xFrom = 800;
	surface3->yFrom = 420;
	surface3->xTo = 1200;
	surface3->yTo = 420;

	Surface * surface4 = new Surface();
	surface4->xFrom = 50;
	surface4->yFrom = 380;
	surface4->xTo = 90;
	surface4->yTo = 380;

	Surface * surface5 = new Surface();
	surface5->xFrom = 510;
	surface5->yFrom = 380;
	surface5->xTo = 560;
	surface5->yTo = 380;

	Surface * surface6 = new Surface();
	surface6->xFrom = 1000;
	surface6->yFrom = 380;
	surface6->xTo = 1200;
	surface6->yTo = 380;

	Surface * surface7 = new Surface();
	surface7->xFrom = 900;
	surface7->yFrom = 230;
	surface7->xTo = 1100;
	surface7->yTo = 230;

	surfaces->push_back(surface1);
	surfaces->push_back(surface2);
	surfaces->push_back(surface3);
	surfaces->push_back(surface4);
	surfaces->push_back(surface5);
	surfaces->push_back(surface6);
	surfaces->push_back(surface7);

	SetLevelLength();
	surfaceLevelView = new SurfaceLevelView(surfaces);
	surfaceLevelView->registerToGraphics();
}

void SurfaceLevel::SetLevelLength()
{
	int maxX = 0;
	vector<Surface*>::iterator iterator = surfaces->begin();
	while(iterator != surfaces->end())
	{
		Surface * surface = *iterator;
		if(maxX < surface->xTo)
		{
			maxX = surface->xTo;
		}
		iterator++;
	}
	levelLength = maxX;
}

SurfaceLevel::~SurfaceLevel(){
  if(pInstance != 0)delete pInstance;
}

void SurfaceLevel::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
{
	Location * fromLocation;
	Location * toLocation;
	float fromLocationY;
	float toLocationY;
	bool isFalling;
	bool hitHead;
	Surface * onSurface;
	vector<Surface*>::iterator iterator;

	switch (message) 
	{
	case CM_KEY:
		break;
	case CM_LEVEL_START:
		MessageQueue::Inst()->sendMessage(CM_LEVEL_LENGTH, levelLength, NULL);
		break;
	case CM_CHARACTER_MOVE_X_FROM_TO:
		fromLocation = (Location*)wParam;
		toLocation = (Location*)lParam;
		iterator = surfaces->begin();
		while(iterator != surfaces->end())
		{
			iterator++;
		}
		break;

	case CM_CHARACTER_MOVE_Y_FROM_TO:
		fromLocation = (Location*)wParam;
		toLocation = (Location*)lParam;
		fromLocationY = fromLocation->Y + fromLocation->height;
		toLocationY = toLocation->Y + toLocation->height;
		
		if(toLocationY > fromLocationY || toLocationY == fromLocationY)
		{
			isFalling = true;
			iterator = surfaces->begin();
			while(iterator != surfaces->end())
			{
				Surface * surface = *iterator;
				
				if((surface->yFrom <= toLocationY && surface->yFrom >= fromLocationY) || (toLocationY > fromLocationY && surface->yFrom < toLocationY) )
				{
					if(surface->xFrom <= toLocation->X && surface->xTo >= (toLocation->X + toLocation->width))
					{
						isFalling = false;
						onSurface = surface;
					}
					if(surface->xFrom >= toLocation->X && surface->xTo <= (toLocation->X + toLocation->width))
					{
						isFalling = false;
						onSurface = surface;
					}
					if(surface->xFrom <= toLocation->X && surface->xTo <= (toLocation->X + toLocation->width) && surface->xTo > toLocation->X)
					{
						isFalling = false;
						onSurface = surface;
					}
					if(surface->xFrom >= toLocation->X && surface->xFrom <= (toLocation->X + toLocation->width) && surface->xTo >= (toLocation->X + toLocation->width))
					{
						isFalling = false;
						onSurface = surface;
					}
				}
		
				iterator++;
			}
			if(isFalling)
			{
				MessageQueue::Inst()->sendMessage(CM_CHARACTER_IS_FALLING, NULL, NULL);
			}
			else
			{
				MessageQueue::Inst()->sendMessage(CM_CHARACTER_IS_STANDING, (int)onSurface, NULL);
			}
		}
		else
		{
			hitHead = false;
			iterator = surfaces->begin();
			while(iterator != surfaces->end())
			{

			}
		}
		break;
	}
}