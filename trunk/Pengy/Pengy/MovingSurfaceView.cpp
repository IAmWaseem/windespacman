#include "MovingSurfaceView.h"

MovingSurfaceView::MovingSurfaceView(void)
{
	this->pSurface = NULL;
}
MovingSurfaceView::MovingSurfaceView(MovingSurface * surface)
{
	this->pSurface = surface;
}

void MovingSurfaceView::Draw(HDC hdc, RECT rect, int xFrom, int xTo)
{
	if(pSurface != NULL)
		Rectangle(hdc, pSurface->xFrom - xFrom, pSurface->yFrom, pSurface->xTo - xFrom, pSurface->yFrom + (pSurface->yTo - pSurface->yFrom));
}

MovingSurfaceView::~MovingSurfaceView(void)
{
}
