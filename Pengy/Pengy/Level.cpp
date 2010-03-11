#include "Level.h"
#include "Location.h"
#include "Math.h"
#include "Waldo.h"

Level* Level::pInstance = NULL;

Level* Level::Inst(){
  if(pInstance == NULL){
    pInstance = new Level();
  }
  return pInstance;
}

Level::Level()
{ 
	//default level 1
	surfaces = beach.getSurfaces();
	SetLevelLength();
}

void Level::SetLevelLength()
{
	int maxX = 0;
	vector<Surface*>::iterator iterator = surfaces.begin();
	while(iterator != surfaces.end())
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

Level::~Level(){
  if(pInstance != 0)delete pInstance;
}

void Level::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
{
	Location * gL1 = new Location();
	Location * gL2 = new Location();
	Location * gL3 = new Location();
	Location * gL4 = new Location();

	gL1->X = 400;
	gL1->Y = 300;

	gL2->X = 200;
	gL2->Y = 300;

	gL3->X = 300;
	gL3->Y = 300;

	Location * fromLocation;
	Location * toLocation;
	float fromLocationY;
	float toLocationY;
	float fromLocationYdiff;
	float toLocationYdiff;
	bool isFalling;
	bool bumpHead;
	bool hit;
	vector<Surface*>::iterator iterator;
	Surface * onSurface;
	
	switch (message) 
	{
	case CM_KEY:
		break;
	case CM_LEVEL_LOAD:
		LoadLevel(world->Inst()->level);
		MessageQueue::Inst()->sendMessage(CM_LEVEL_LENGTH, levelLength, NULL);
		MessageQueue::Inst()->sendMessage(CM_GADGETFACTORY_CREATE_PIRANHA, (int)gL1, NULL);
		MessageQueue::Inst()->sendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)gL2, NULL);
		MessageQueue::Inst()->sendMessage(CM_GADGETFACTORY_CREATE_GOLDFISH, (int)gL3, NULL);
		MessageQueue::Inst()->sendMessage(CM_ENEMYFACTORY_CREATE_WALDO_PATROL, (int)surfaces.at(4), NULL);
		MessageQueue::Inst()->sendMessage(CM_ENEMYFACTORY_CREATE_WALDO_PATROL, (int)surfaces.at(9), NULL);
		MessageQueue::Inst()->sendMessage(CM_ENEMYFACTORY_CREATE_WALDO_PATROL, (int)surfaces.at(11), NULL);
		MessageQueue::Inst()->sendMessage(CM_ENEMYFACTORY_CREATE_WALDO_PATROL, (int)surfaces.at(10), NULL);
		MessageQueue::Inst()->sendMessage(CM_ENEMYFACTORY_CREATE_WALDO_PATROL, (int)surfaces.at(13), NULL);
		break;
	case CM_CHARACTER_MOVE_X_FROM_TO:
		fromLocation = (Location*)wParam;
		toLocation = (Location*)lParam;
		iterator = surfaces.begin();
		hit = false;
		if(fromLocation->X < toLocation->X)
		{
			while(iterator != surfaces.end())
			{
				Surface * surface = *iterator;
				if(LocationInSurfaceY(toLocation, surface))
				{
					if(!surface->isCloud && ((fromLocation->X + fromLocation->width) <= surface->xFrom && (toLocation->X + toLocation->width) >= surface->xFrom))
					{
						MessageQueue::Inst()->sendMessage(CM_CHARACTER_BUMPS_INTO, (int)surface, NULL);
					}
				}
				iterator++;
			}
		}
		else
		{
			while(iterator != surfaces.end())
			{
				Surface * surface = *iterator;
				if(LocationInSurfaceY(toLocation, surface))
				{
					if(!surface->isCloud && (fromLocation->X >= surface->xTo && toLocation->X <= surface->xTo))
					{
						MessageQueue::Inst()->sendMessage(CM_CHARACTER_BUMPS_INTO, (int)surface, NULL);
					}
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
			MessageQueue::Inst()->sendMessage(CM_CHARACTER_JUMPING_BUMPS_HEAD, (int)onSurface, NULL);
		}
		break;
	}
}

bool Level::LocationInSurfaceX(Location * location, Surface * surface)
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

bool Level::LocationInSurfaceY(Location * location, Surface * surface)
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

void Level::LoadLevel(int level)
{
	vector<Tile> myTiles;
	vector<int*> data;
	LPCSTR path = "";

	switch(level)
	{
	case 1:
		
		path = "res/tilemap.bmp";
		data = beach.getTiles();
		surfaces = beach.getSurfaces();
		SetLevelLength();
		break;
	//case 2:
	//	path = "res/Summer.bmp";
	//	data = GetLevel1Array();
	//	break;
	//case 3:
	//	path = "res/Summer.bmp";
	//	data = GetLevel1Array();
	//	break;
	default:
		//level1
		path = "res/tilemap.bmp";
		data = beach.getTiles();
		surfaces = beach.getSurfaces();
		SetLevelLength();
		break;
	}

	vector<int*>::iterator iterator = data.begin();
	while(iterator!=data.end())
	{
		

		int* dataRow = *iterator;

		int i = dataRow[5];

		if(dataRow[4] == 1)
			myTiles.push_back(Tile(dataRow[0], dataRow[1], dataRow[2], dataRow[3], true, dataRow[5]));
		else
			myTiles.push_back(Tile(dataRow[0], dataRow[1], dataRow[2], dataRow[3], false, dataRow[5]));

		iterator++;
	}

	levelView.SetSurface(&surfaces);
	levelView.SetTiles(myTiles, path);
}