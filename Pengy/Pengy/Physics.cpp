#include "Physics.h"
#include "Win.h"

Physics::Physics(void)
{

}

Physics::~Physics(void)
{

}


bool Physics::MoveXFromTo(Location * pFromLocation,Location * pToLocation,vector<Surface*> surfaces) 
{
	vector<Surface*>::iterator iterator;
	iterator = surfaces.begin();

	if(pFromLocation->X < pToLocation->X)
	{
		while(iterator != surfaces.end())
		{
			Surface * pSurface = *iterator;
			if(LocationInSurfaceY(pToLocation, pSurface))
			{
				if(!pSurface->isCloud && ((pFromLocation->X + pFromLocation->width) <= pSurface->xFrom && (pToLocation->X + pToLocation->width) >= pSurface->xFrom))
				{
					pSurfaceFinal = pSurface;
					return true;
				}
			}
			iterator++;
		}
	}
	else
	{
		while(iterator != surfaces.end())
		{
			Surface * pSurface = *iterator;
			if(LocationInSurfaceY(pToLocation, pSurface))
			{
				if(!pSurface->isCloud && (pFromLocation->X >= pSurface->xTo && pToLocation->X <= pSurface->xTo))
				{
					pSurfaceFinal=pSurface;
					return true;	
				}
			}
			iterator++;
		}		
	}
	return false;
}

bool Physics::FallYFromTo(Location * pFromLocation,Location * pToLocation,vector<Surface*> surfaces) 
{
	bool isFalling;
	vector<Surface*>::iterator iterator;
	Surface * pOnSurface;
	//float fromLocationYdiff;
	float toLocationYdiff;
	float fromLocationY;
	float toLocationY;
	fromLocationY = pFromLocation->Y + pFromLocation->height;
	toLocationY = pToLocation->Y + pToLocation->height;
	isFalling = true;
	iterator = surfaces.begin();
	while(iterator != surfaces.end())
	{
		Surface * pSurface = *iterator;
		//fromLocationYdiff = fabs(fromLocationY - pSurface->xFrom);
		toLocationYdiff = fabs(toLocationY - pSurface->yFrom);
		
		if(LocationInSurfaceX(pToLocation, pSurface))
		{
			if(pSurface->isSlope!=0 && SlopeInSurfaceX(pToLocation, pSurface))
			{
				if(pSurface->isSlope==1)
				{
					if(toLocationY >= pSurface->SlopeCoefficientB + (pSurface->SlopeCoefficientA * pToLocation->X ))
					{
						isFalling = false;
						pOnSurface = new Surface;	
						pOnSurface->isSurfaceOfDeath = false;
						pOnSurface->yFrom = toLocationY;
					}
				}
				else
				{
					if(toLocationY >= pSurface->SlopeCoefficientB + (pSurface->SlopeCoefficientA * (pToLocation->width + pToLocation->X)))
					{
						isFalling = false;
						pOnSurface = new Surface;		
						pOnSurface->isSurfaceOfDeath = false;
						pOnSurface->yFrom = toLocationY;
					}
				}
				
			}
			else if((pSurface->yFrom <= toLocationY && pSurface->yFrom >= fromLocationY) || toLocationYdiff < 5)
			{
				if(pSurface->isCloud && CWin::keystateDown != 0)
				{

				}
				else
				{
					isFalling = false;
					pOnSurface = pSurface;
				}
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
		pOnSurfaceFinalFall = pOnSurface;
		return true;
	}
}

bool Physics::JumpYFromTo(Location * pFromLocation, Location * pToLocation, vector<Surface*> surfaces) 
{
	//float fromLocationYdiff;
	float toLocationYdiff;
	float fromLocationY;
	float toLocationY;
	fromLocationY = pFromLocation->Y;
	toLocationY = pToLocation->Y;
	//bool hit;
	vector<Surface*>::iterator iterator;
	Surface * pOnSurface;
	bool bumpHead;
	bumpHead = false;
	iterator = surfaces.begin();
	while(iterator != surfaces.end())
	{
		Surface * pSurface = *iterator;
		//fromLocationYdiff = fabs(fromLocationY - pSurface->xTo);
		toLocationYdiff = fabs(toLocationY - pSurface->yTo);
		
		if(LocationInSurfaceX(pToLocation, pSurface))
		{
			if((pSurface->yTo >= toLocationY && pSurface->yTo <= fromLocationY) || toLocationYdiff < 5)
			{
				if(!pSurface->isCloud)
					bumpHead = true;
					pOnSurface = pSurface;
				}
			}
			
			iterator++;
		}
		if(bumpHead)
		{
			pOnSurfaceFinalJump=pOnSurface;
			return true;
		}
		return false;
}

bool Physics::LocationInSurfaceX(Location * pLocation, Surface * pSurface)
{
	bool inSurface = false;
	if(pSurface->xFrom <= pLocation->X && pSurface->xTo >= (pLocation->X + pLocation->width))
	{
		inSurface = true;
	}
	if(pSurface->xFrom >= pLocation->X && pSurface->xTo <= (pLocation->X + pLocation->width))
	{
		inSurface = true;
	}
	if(pSurface->xFrom <= pLocation->X && pSurface->xTo <= (pLocation->X + pLocation->width) && pSurface->xTo > pLocation->X)
	{
		inSurface = true;
	}
	if(pSurface->xFrom >= pLocation->X && pSurface->xFrom <= (pLocation->X + pLocation->width) && pSurface->xTo >= (pLocation->X + pLocation->width))
	{
		inSurface = true;
	}
	return inSurface;
}

bool Physics::LocationInSurfaceY(Location * pLocation, Surface * pSurface)
{
	bool inSurface = false;
	if(pSurface->yFrom  >= pLocation->Y && pSurface->yTo <= (pLocation->Y + pLocation->height))
	{
		inSurface = true;
	}
	if(pSurface->yFrom  <= pLocation->Y && pSurface->yTo >= (pLocation->Y + pLocation->height))
	{
		inSurface = true;
	}
	if(pLocation->Y >= pSurface->yFrom && pLocation->Y <= pSurface->yTo)
	{
		inSurface = true;
	}
	if((pLocation->Y + pLocation->height) >= pSurface->yFrom && (pLocation->Y + pLocation->height) <= pSurface->yTo)
	{
		inSurface = true;
	}
	return inSurface;
}

bool Physics::SlopeInSurfaceX(Location * location, Surface * surface)
{
	bool inSurface = true;

	if(surface->isSlope == 1)
	{
		if(surface->xFrom >= location->X)
		{
			inSurface = false;
		}
	}
	else
	{
		if(surface->xTo <= location->X + location->width)
		{
			inSurface = false;
		}
	}
	return inSurface;
}