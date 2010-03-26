#include "GadgetView.h"
#include "Gadget.h"
#include "Renderer.h"
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
		gadget->GetLocation()->height = b->Height();
		gadget->GetLocation()->width = b->Width();
		mask = CreateBitmapMask(bitmap, RGB(0, 0, 0), width_height[0], width_height[1]);
		break;
	case GadgetImage::SnowBall:
		bitmap = LoadImage(NULL, SNOWBALL_IMAGE, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		b->LoadDIBFile(SNOWBALL_IMAGE);
		width_height[0] = b->Width();
		width_height[1] = b->Height();
		mask = CreateBitmapMask(bitmap, RGB(0, 0, 0), width_height[0], width_height[1]);
		break;
	case GadgetImage::Balloons:

		break;
	case GadgetImage::ExtraLife:
		bitmap = LoadImage(NULL, EXTRALIFE_IMAGE, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		b->LoadDIBFile(EXTRALIFE_IMAGE);
		width_height[0] = b->Width();
		width_height[1] = b->Height();
		mask = CreateBitmapMask(bitmap, RGB(0, 0, 0), width_height[0], width_height[1]);
		break;

	case GadgetImage::RottenFish:
		bitmap = LoadImage(NULL, ROTTENFISH_IMAGE, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		b->LoadDIBFile(ROTTENFISH_IMAGE);
		width_height[0] = b->Width();
		width_height[1] = b->Height();
		gadget->GetLocation()->height = b->Height();
		gadget->GetLocation()->width = b->Width();
		mask = CreateBitmapMask(bitmap, RGB(0, 0, 0), width_height[0], width_height[1]);
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

	case GadgetImage::Switch:
		bitmap = LoadImage(NULL, SWITCH_IMAGE, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		b->LoadDIBFile(SWITCH_IMAGE);
		width_height[0] = b->Width();
		width_height[1] = b->Height();
		mask = CreateBitmapMask(bitmap, RGB(0, 0, 0), width_height[0], width_height[1]);
		break;

	case GadgetImage::SnowBoots:
		bitmap = LoadImage(NULL, SNOWBOOTS_IMAGE, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		b->LoadDIBFile(SNOWBOOTS_IMAGE);
		width_height[0] = b->Width();
		width_height[1] = b->Height();
		mask = CreateBitmapMask(bitmap, RGB(0, 0, 0), width_height[0], width_height[1]);
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
	if(!pWorld->Instance()->menu)
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

		if(x + width >= xFrom && x <= xTo)
		{
			BitBltTransparant(hdc, x + difWidth - xFrom, y + difHeight, imageW, imageH, bufDC, 0, 0, bitmap, mask);
		}

		DeleteDC(bufDC);

		#pragma region debug
		if(Renderer::ShowDebug)
		{	
			// lines of the border of the image current used by pengy
			POINT leftOfPengy[2];	
			leftOfPengy[0].x = x - xFrom;
			leftOfPengy[0].y = y;
			leftOfPengy[1].x = x - xFrom;
			leftOfPengy[1].y = y + height;
			
			POINT bottomOfPengy[2]; 
			bottomOfPengy[0].x = x - xFrom;
			bottomOfPengy[0].y = y + height;
			bottomOfPengy[1].x = x + width - xFrom;
			bottomOfPengy[1].y = y + height;
			
			POINT topOfPengy[2];	
			topOfPengy[0].x = x - xFrom;
			topOfPengy[0].y = y;
			topOfPengy[1].x = x + width - xFrom;
			topOfPengy[1].y = y;
			
			POINT rightOfPengy[2];	
			rightOfPengy[0].x = x + width - xFrom;
			rightOfPengy[0].y = y;
			rightOfPengy[1].x= x + width - xFrom;
			rightOfPengy[1].y = y + height;

			HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
			SelectObject(hdc, hPen);

			// draw the lines
			Polyline(hdc, leftOfPengy, 2);
			Polyline(hdc, bottomOfPengy, 2);
			Polyline(hdc, topOfPengy, 2);
			Polyline(hdc, rightOfPengy, 2);

			DeleteObject(hPen);
		}
#pragma endregion

	}
}