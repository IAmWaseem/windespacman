#pragma once
#include "gadget.h"
#include "available.h"
#include "observer.h"
#include "direction.h"

class Weapon : public Gadget, public Available, public Observer
{
public:
	Weapon(Location * pLocation, GadgetView::GadgetImage gadgetImage, Direction direction, float speed, int maxDistance);
	~Weapon(void);
	void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
	void Update(int timeElapsed);
private:
	Direction direction;
	float speed;
	int maxDistance;
	int distanceCovered;
};
