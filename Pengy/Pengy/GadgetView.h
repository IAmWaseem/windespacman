#pragma once
#include <map>
#include "Windows.h"
#include "Bitmap.h"
#include "View.h"
#include "Location.h"
#include "GadgetImages.h"
using namespace std;
using namespace dotnetguy;

class Gadget;

class GadgetView : public View
{
public:
	enum GadgetImage
	{
		SnowBall,
		Goldfish,
		RottenFish,
		ExtraLife,
		Powerup,
		Balloons,
		Piranha,
		Ladybug,
		Switch,
		SnowBoots
	};

	GadgetView(void);
	GadgetView(GadgetImage image, Gadget * gadget);
	~GadgetView(void);

	void Update();
	void Draw(HDC hdc, RECT rect, int xFrom, int xTo);

private:
	GadgetImage currentImage;
	HANDLE currentBitmap;
	HANDLE currentMask;
	int* width_height;
	Gadget * pGadget;
};
