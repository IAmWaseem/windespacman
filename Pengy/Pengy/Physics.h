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
	bool Physics::FallYFromTo(Location * pFromLocation,Location * toLocation,vector<Surface*> surfaces);
	bool Physics::MoveXFromTo(Location * pFromLocation,Location * toLocation,vector<Surface*> surfaces);
	bool Physics::JumpYFromTo(Location * pFromLocation,Location * toLocation,vector<Surface*> surfaces);
	bool LocationInSurfaceX(Location * pLocation, Surface * pSurface);
	bool LocationInSurfaceY(Location * pLocation, Surface * pSurface);
};
