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
	Surface * onSurface_final_jump;
	Surface * onSurface_final_fall;
	Surface * Surface_final;
	bool Physics::Fall_Y_From_To(Location * fromLocation,Location * toLocation,vector<Surface*> surfaces);
	bool Physics::Move_X_From_To(Location * fromLocation,Location * toLocation,vector<Surface*> surfaces);
	bool Physics::Jump_Y_From_To(Location * fromLocation,Location * toLocation,vector<Surface*> surfaces);
	bool LocationInSurfaceX(Location * location, Surface * surface);
	bool LocationInSurfaceY(Location * location, Surface * surface);
};
