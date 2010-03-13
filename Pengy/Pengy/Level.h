#pragma once
#include "Surface.h"
#include "Observer.h"
#include "MessageQueue.h"
#include "LevelView.h"
#include "Location.h"
#include "BeachLevel.h"
#include "World.h"
#include "Physics.h"


class Level : public Observer
{
public:
	static Level* Inst();
    ~Level();
    void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
	void LoadLevel(int level);
protected:
	Level();
private:
	vector<Surface*> surfaces;
    static Level* pInstance;
	LevelView levelView;
	BeachLevel beach;
	Physics physic_behavior;
	int levelLength;
	void SetLevelLength();
	World* world;
	/*bool LocationInSurfaceX(Location * location, Surface * surface);
	bool LocationInSurfaceY(Location * location, Surface * surface);*/
};
