#include "GadgetView.h"
#include "Gadget.h"
using namespace dotnetguy;

GadgetView::GadgetView(GadgetImage image, Gadget * gadget)
{
	currentImage = image;
	HANDLE bitmap;
	HANDLE mask;
	Bitmap * b = new Bitmap();
	width_height = new int[2];
	width_height[0] = 0;
	width_height[1] = 0;
	switch(image)
	{
	case GadgetImage::Goldfish:
		bitmap = LoadImage(NULL, GOLDFISH_IMAGE, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		b->LoadDIBFile(GOLDFISH_IMAGE);
		width_height[0] = b->Width();
		width_height[1] = b->Height();
		mask = CreateBitmapMask(bitmap, RGB(0, 0, 0), width_height[0], width_height[1]);
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
		bitmap = LoadImage(NULL, PIRANHA_IMAGE, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		b->LoadDIBFile(PIRANHA_IMAGE);
		width_height[0] = b->Width();
		width_height[1] = b->Height();
		mask = CreateBitmapMask(bitmap, RGB(0, 0, 0), width_height[0], width_height[1]);
		break;

	case GadgetImage::Ladybug:

		break;

	}
	b->~Bitmap();
	currentMask = mask;
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

void GadgetView::Draw(HDC hdc, RECT rect, int xFrom, int xTo)
{
	if(!world->Inst()->menu)
	{
		HANDLE bitmap = currentBitmap;
		HANDLE mask = currentMask;
		HDC bufDC = CreateCompatibleDC(hdc);
		SelectObject(bufDC, bitmap);

		int x = pGadget->GetLocation()->X;
		int y = pGadget->GetLocation()->Y;
		int width = pGadget->GetLocation()->width;
		int height = pGadget->GetLocation()->height;
		int imageW = width_height[0];
		int imageH = width_height[1];
		int difWidth = (width - imageW) / 2;
		int difHeight = height - imageH;

		if(x + width >= xFrom && x + width <= xTo)
		{
			BitBltTransparant(hdc, x + difWidth - xFrom, y + difHeight, imageW, imageH, bufDC, 0, 0, bitmap, mask);
		}

		DeleteDC(bufDC);
	}
}