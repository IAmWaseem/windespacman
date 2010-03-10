#include "Physics.h"

Physics::Physics(void)
{

}

Physics::~Physics(void)
{

}


//bool Physics::Move_X_From_To_Right(Location * fromLocation,Location * toLocation,vector<Surface*> surfaces,Surface * surface) 
//{
//	if(!surface->isCloud && ((fromLocation->X + fromLocation->width) <= surface->xFrom && (toLocation->X + toLocation->width) >= surface->xFrom))
//	{
//		return true;
//	}
//	return false;
//}
//
//bool Physics::Move_X_From_To_Left(Location * fromLocation,Location * toLocation,vector<Surface*> surfaces,Surface * surface) 
//{
//	if(!surface->isCloud && (fromLocation->X >= surface->xTo && toLocation->X <= surface->xTo))
//	{
//		return true;
//	}
//	return false;
//}

bool Physics::Fall_Y_From_To(Location * fromLocation,Location * toLocation,vector<Surface*> surfaces) 
{
	bool isFalling;
	vector<Surface*>::iterator iterator;
	Surface * onSurface;
	float fromLocationYdiff;
	float toLocationYdiff;
	float fromLocationY;
	float toLocationY;
	fromLocationY = fromLocation->Y + fromLocation->height;
	toLocationY = toLocation->Y + toLocation->height;
	isFalling = true;
	iterator = surfaces.begin();
	while(iterator != surfaces.end())
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
		return false;
	}
	else
	{
		onSurface_final=onSurface;
		return true;
	}
}

bool Physics::Jumo_Y_From_To(Location * fromLocation, Location * toLocation, vector<Surface*> surfaces) 
{
	float fromLocationYdiff;
	float toLocationYdiff;
	float fromLocationY;
	float toLocationY;
	fromLocationY = fromLocation->Y;
	toLocationY = toLocation->Y;
	bool hit;
	vector<Surface*>::iterator iterator;
	Surface * onSurface;
	bool bumpHead;
	fromLocationY = fromLocation->Y;
	toLocationY = toLocation->Y;
	bumpHead = false;
	iterator = surfaces.begin();
	while(iterator != surfaces.end())
	{
		Surface * surface = *iterator;
		fromLocationYdiff = fabs(fromLocationY - surface->xTo);
		toLocationYdiff = fabs(toLocationY - surface->yTo);
		
		if(LocationInSurfaceX(toLocation, surface))
		{
			if((surface->yTo >= toLocationY && surface->yTo <= fromLocationY) || toLocationYdiff < 5)
			{
				if(!surface->isCloud)
					bumpHead = true;
					onSurface = surface;
				}
			}
			
			iterator++;
		}
		if(bumpHead)
		{
			onSurface_final=onSurface;
			return true;
		}
		return false;
}

bool Physics::LocationInSurfaceX(Location * location, Surface * surface)
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

bool Physics::LocationInSurfaceY(Location * location, Surface * surface)
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
	if((location->Y + location->height) >= surface->yFrom && (location->Y + location->height) <= surface->yTo)
	{
		inSurface = true;
	}
	return inSurface;
}