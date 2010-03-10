#include "WaldoView.h"
#include "Waldo.h"
#include "Bitmap.h"


WaldoView::WaldoView(Waldo * pWaldo)
{
	this->pWaldo = pWaldo;
	pBitmap = new Bitmap();
	pBitmap->LoadDIBFile("res/Waldo.bmp");
}

WaldoView::~WaldoView(void)
{
}

void WaldoView::Draw(HDC hDC, RECT rect, int xFrom, int xTo)
{
	RECT placeRect;
	placeRect.left = (LONG)(pWaldo->GetLocation()->X - xFrom);
	placeRect.top = (LONG)(pWaldo->GetLocation()->Y);
	placeRect.right = placeRect.left + pBitmap->Width();
	placeRect.bottom = placeRect.top + pBitmap->Height();
	pWaldo->GetLocation()->width = (float)pBitmap->Width();
	pWaldo->GetLocation()->height = (float)pBitmap->Height();
	if(pWaldo->GetLocation()->X + pWaldo->GetLocation()->width >= xFrom && pWaldo->GetLocation()->X + pWaldo->GetLocation()->width <= xTo)
	{
		pBitmap->TransparentPaint(hDC, RGB(0, 0, 0), &placeRect, NULL); 
	}
}
