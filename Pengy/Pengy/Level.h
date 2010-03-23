#pragma once
#include "Surface.h"
#include "Observer.h"
#include "MessageQueue.h"
#include "LevelView.h"
#include "Location.h"
#include "BeachLevel.h"
#include "World.h"
#include "Physics.h"
#include "MovingSurface.h"
#include "SnowLevel.h"

class Level : public Observer
{
public:
	static Level* Instance();
    ~Level();
    void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
	void LoadLevel(int level);
protected:
	Level();
private:
	vector<Surface*> surfaces;
	vector<MovingSurface*> movingSurfaces;
    static Level* pInstance;
	LevelView levelView;
	BeachLevel beach;
	Physics physic_behavior;
	int levelLength;
	void SetLevelLength();
	World* pWorld;
	/*bool LocationInSurfaceX(Location * location, Surface * surface);
	bool LocationInSurfaceY(Location * location, Surface * surface);*/
};
