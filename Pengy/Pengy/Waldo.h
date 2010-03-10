#pragma once
#include "observer.h"
#include "surface.h"
#include "location.h"

class WaldoView;

class Waldo : public Observer
{

private:
	Location * location;
	WaldoView * waldoView;
public:
	Waldo(Location * location);
	Waldo(Surface * surface);
	~Waldo(void);
	void recieveMessage(UINT message, WPARAM wParam, LPARAM lParam);
	Location * GetLocation();
};
