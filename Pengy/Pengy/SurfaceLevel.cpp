#include "SurfaceLevel.h"
#include "Location.h"
#include "Math.h"

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
	surface1->yTo = 493;

	Surface * surface2 = new Surface();
	surface2->xFrom = 586;
	surface2->yFrom = 483;
	surface2->xTo = 800;
	surface2->yTo = 493;

	Surface * surface3 = new Surface();
	surface3->xFrom = 800;
	surface3->yFrom = 420;
	surface3->xTo = 1200;
	surface3->yTo = 430;

	Surface * surface4 = new Surface();
	surface4->xFrom = 50;
	surface4->yFrom = 380;
	surface4->xTo = 90;
	surface4->yTo = 390;

	Surface * surface5 = new Surface();
	surface5->xFrom = 510;
	surface5->yFrom = 380;
	surface5->xTo = 560;
	surface5->yTo = 390;

	Surface * surface6 = new Surface();
	surface6->xFrom = 1000;
	surface6->yFrom = 300;
	surface6->xTo = 1200;
	surface6->yTo = 327;

	Surface * surface7 = new Surface();
	surface7->xFrom = 900;
	surface7->yFrom = 230;
	surface7->xTo = 1100;
	surface7->yTo = 240;

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
	float fromLocationYdiff;
	float toLocationYdiff;
	bool isFalling;
	bool bumpHead;
	bool hit;
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
		hit = false;
		if(fromLocation->X < toLocation->X)
		{
			while(iterator != surfaces->end())
			{
				Surface * surface = *iterator;
				if(LocationInSurfaceY(toLocation, surface))
				{
					if((fromLocation->X + fromLocation->width) <= surface->xFrom && (toLocation->X + toLocation->width) >= surface->xFrom)
					{
						MessageQueue::Inst()->sendMessage(CM_CHARACTER_BUMPS_INTO, (int)surface, NULL);
					}
				}
				iterator++;
			}
		}
		else
		{
			while(iterator != surfaces->end())
			{
				Surface * surface = *iterator;
				if(LocationInSurfaceY(toLocation, surface))
				{
					//MessageQueue::Inst()->sendMessage(CM_CHARACTER_BUMPS_INTO, (int)onSurface, NULL);
				}
				iterator++;
			}		
		}
		
		break;

	case CM_CHARACTER_FALL_Y_FROM_TO:
		fromLocation = (Location*)wParam;
		toLocation = (Location*)lParam;
		fromLocationY = fromLocation->Y + fromLocation->height;
		toLocationY = toLocation->Y + toLocation->height;

		isFalling = true;
		iterator = surfaces->begin();
		while(iterator != surfaces->end())
		{
			Surface * surface = *iterator;
			fromLocationYdiff = fabs(fromLocationY - surface->xFrom);
			toLocationYdiff = fabs(toLocationY - surface->yFrom);
			
			if(LocationInSurfaceX(toLocation, surface))
			{
				if((surface->yFrom <= toLocationY && surface->yFrom >= fromLocationY) || toLocationYdiff < 5)
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
		break;
	case CM_CHARACTER_JUMP_Y_FROM_TO:
		fromLocation = (Location*)wParam;
		toLocation = (Location*)lParam;
		fromLocationY = fromLocation->Y;
		toLocationY = toLocation->Y;

		bumpHead = false;
		iterator = surfaces->begin();
		while(iterator != surfaces->end())
		{
			Surface * surface = *iterator;
			fromLocationYdiff = fabs(fromLocationY - surface->xTo);
			toLocationYdiff = fabs(toLocationY - surface->yTo);
			
			if(LocationInSurfaceX(toLocation, surface))
			{
				if((surface->yTo >= toLocationY && surface->yTo <= fromLocationY) || toLocationYdiff < 5)
				{
					bumpHead = true;
					onSurface = surface;
				}
			}
			
			iterator++;
		}
		if(bumpHead)
		{
			MessageQueue::Inst()->sendMessage(CM_CHARACTER_JUMPING_BUMPS_HEAD, (int)onSurface, NULL);
		}
		break;
	}
}

bool SurfaceLevel::LocationInSurfaceX(Location * location, Surface * surface)
{
	bool inSurface = false;
	if(surface->xFrom <= location->X && surface->xTo >= (location->X + location->width))
	{
		inSurface = true;
	}
	if(surface->xFrom >= location->X && surface->xTo <= (location->X + location->width))
	{
		inSurface = true;
	}
	if(surface->xFrom <= location->X && surface->xTo <= (location->X + location->width) && surface->xTo > location->X)
	{
		inSurface = true;
	}
	if(surface->xFrom >= location->X && surface->xFrom <= (location->X + location->width) && surface->xTo >= (location->X + location->width))
	{
		inSurface = true;
	}
	return inSurface;
}

bool SurfaceLevel::LocationInSurfaceY(Location * location, Surface * surface)
{
	bool inSurface = false;
	if(surface->yFrom  >= location->Y && surface->yTo <= (location->Y + location->height))
	{
		inSurface = true;
	}
	if(surface->yFrom  <= location->Y && surface->yTo >= (location->Y + location->height))
	{
		inSurface = true;
	}
	if(location->Y >= surface->yFrom && location->Y <= surface->yTo)
	{
		inSurface = true;
	}
	return inSurface;
}