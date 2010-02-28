#include "SurfaceLevelView.h"
#include "Win.h"

SurfaceLevelView::SurfaceLevelView(void)
{
}

SurfaceLevelView::SurfaceLevelView(vector<Surface*> * surfaces)
{
	this->surfaces = surfaces;
}

SurfaceLevelView::~SurfaceLevelView(void)
{
}

void SurfaceLevelView::Draw(HDC hdc, int xFrom, int xTo)
{
	HPEN hPen = CreatePen(PS_DASHDOTDOT, 1, RGB(255, 25, 5));
    SelectObject(hdc, hPen);

	vector<Surface*>::iterator iterator = surfaces->begin();
	while(iterator != surfaces->end())
	{
		Surface * surface = *iterator;
		Rectangle(hdc, surface->xFrom - xFrom, surface->yFrom, surface->xTo - xFrom, surface->yFrom + 10);
		iterator++;
	}
	DeleteObject(hPen);
}