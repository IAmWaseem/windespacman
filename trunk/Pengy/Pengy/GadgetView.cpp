#include "GadgetView.h"
#include "Gadget.h"
using namespace dotnetguy;

GadgetView::GadgetView(GadgetImage image, Gadget * gadget)
{
	currentImage = image;
	Bitmap * bitmap = new Bitmap();
	switch(image)
	{
	case GadgetImage::Goldfish:
		bitmap->LoadDIBFile(GOLDFISH_IMAGE);
		break;
	case GadgetImage::SnowBall:

		break;
	case GadgetImage::Balloons:

		break;
	case GadgetImage::ExtraLife:

		break;

	case GadgetImage::RottenFish:

		break;

	case GadgetImage::Powerup:

		break;

	case GadgetImage::Piranha:
		bitmap->LoadDIBFile(PIRANHA_IMAGE);
		break;

	case GadgetImage::Ladybug:

		break;

	}
	currentBitmap = bitmap;
	this->pGadget = gadget;
}

GadgetView::GadgetView(void)
{
}

GadgetView::~GadgetView(void)
{
}

void GadgetView::Update()
{

}

void GadgetView::Draw(HDC hdc, int xFrom, int xTo)
{
	Bitmap * bitmap = currentBitmap;
	RECT placeRect;
	placeRect.left = (LONG)(pGadget->GetLocation()->X - xFrom);
	placeRect.top = (LONG)(pGadget->GetLocation()->Y);
	placeRect.right = placeRect.left + bitmap->Width();
	placeRect.bottom = placeRect.top + bitmap->Height();
	pGadget->GetLocation()->width = (float)bitmap->Width();
	pGadget->GetLocation()->height = (float)bitmap->Height();
	if(pGadget->GetLocation()->X + pGadget->GetLocation()->width >= xFrom && pGadget->GetLocation()->X + pGadget->GetLocation()->width <= xTo)
	{
		bitmap->TransparentPaint(hdc, RGB(0, 0, 0), &placeRect, NULL); 
	}
}