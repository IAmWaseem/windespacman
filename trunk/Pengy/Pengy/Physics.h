#pragma once
#include "Location.h"
#include "Surface.h"
#include "Math.h"

#include "Observer.h"
#include "MessageQueue.h"
#include "LevelView.h"
#include "BeachLevel.h"
#include "World.h"


class Physics
{
public:
	Physics(void);
	~Physics(void);
	Surface * pOnSurfaceFinalJump;
	Surface * pOnSurfaceFinalFall;
	Surface * pSurfaceFinal;
	bool FallYFromTo(Location * pFromLocation,Location * pToLocation,vector<Surface*> surfaces);
	bool MoveXFromTo(Location * pFromLocation,Location * pToLocation,vector<Surface*> surfaces);
	bool JumpYFromTo(Location * pFromLocation,Location * pToLocation,vector<Surface*> surfaces);
	bool LocationInSurfaceX(Location * pLocation, Surface * pSurface);
	bool LocationInSurfaceY(Location * pLocation, Surface * pSurface);
};
