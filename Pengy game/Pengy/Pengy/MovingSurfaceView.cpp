#include "MovingSurfaceView.h"
#include "MovingSurface.h"
#include "MovingSurfaceImages.h"

MovingSurfaceView::MovingSurfaceView(void)
{
	this->pSurface = NULL;
}
MovingSurfaceView::MovingSurfaceView(MovingSurface * surface, MovingSurfaceType type)
{
	this->pSurface = surface;
	HANDLE bitmap;
	HANDLE mask;
	Bitmap * b = new Bitmap();
	width_height = new int[2];
	width_height[0] = 0;
	width_height[1] = 0;

	switch(type)
	{
	case MovingSurfaceType::SurfBoard:
		bitmap = LoadImage(NULL, SURFBOARD_IMAGE, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		b->LoadDIBFile(SURFBOARD_IMAGE);
		width_height[0] = b->Width();
		width_height[1] = b->Height();
		mask = CreateBitmapMask(bitmap, RGB(0, 0, 0), width_height[0], width_height[1]);
		break;
	case MovingSurfaceType::Plank:
		bitmap = LoadImage(NULL, PLANK_IMAGE, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		b->LoadDIBFile(PLANK_IMAGE);
		width_height[0] = b->Width();
		width_height[1] = b->Height();
		mask = CreateBitmapMask(bitmap, RGB(0, 0, 0), width_height[0], width_height[1]);
		break;
	}
	currentMask = mask;
	currentBitmap = bitmap;
	pSurface->yTo = pSurface->yFrom + b->Height();
	pSurface->xTo = pSurface->xFrom + b->Width();
	delete b;
}

void MovingSurfaceView::Draw(HDC hdc, RECT rect, int xFrom, int xTo)
{
	if(!pWorld->Instance()->menu && pSurface != NULL)
	{
		HANDLE bitmap = currentBitmap;
		HANDLE mask = currentMask;
		HDC bufDC = CreateCompatibleDC(hdc);
		SelectObject(bufDC, bitmap);

		int x = pSurface->xFrom;
		int y = pSurface->yFrom;
		int width= width_height[0];
		int height = width_height[1];

		if(x + width >= xFrom && x <= xTo)
		{
			BitBltTransparant(hdc, x - xFrom, y, width, height, bufDC, 0, 0, bitmap, mask);
		}

		DeleteDC(bufDC);
	}
}

MovingSurfaceView::~MovingSurfaceView(void)
{
}
