#pragma once
#include "Location.h"
#include "Direction.h"

class Enemy
{
public:
	Enemy(void);
	~Enemy(void);

protected:
	Location * pLocation;
	Direction direction;
};
