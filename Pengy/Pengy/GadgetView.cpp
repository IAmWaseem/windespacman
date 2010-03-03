#include "GadgetView.h"
#include "Gadget.h"
using namespace dotnetguy;

GadgetView::GadgetView(GadgetImage image, LPCSTR path, Gadget * gadget)
{
	currentImage = image;
	Bitmap * bitmap = new Bitmap();
	bitmap->LoadDIBFile(path);
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
	placeRect.left = pGadget->GetLocation()->X - xFrom;
	placeRect.top = pGadget->GetLocation()->Y;
	placeRect.right = placeRect.left + bitmap->Width();
	placeRect.bottom = placeRect.top + bitmap->Height();
	pGadget->GetLocation()->width = bitmap->Width();
	pGadget->GetLocation()->height = bitmap->Height();
	bitmap->TransparentPaint(hdc, RGB(0, 0, 0), &placeRect, NULL); 
}