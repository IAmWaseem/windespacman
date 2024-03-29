#include "LeafEyeView.h"
#include "LeafEye.h"
#include "Bitmap.h"
#include "Renderer.h"


LeafEyeView::LeafEyeView(LeafEye * pLeafEye)
{
	this->pLeafEye = pLeafEye;

	Bitmap * b = new Bitmap();
	b->LoadDIBFile("res/Leafeye.bmp");
	width_height = new int[2]; width_height[0] = b->Width(); width_height[1] = b->Height();
	b->~Bitmap();

	pBitmapLeft = LoadImage(NULL, "res/Leafeye.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	pMaskLeft = CreateBitmapMask(pBitmapLeft, RGB(0, 0, 0), width_height[0], width_height[1]);
	pBitmapRight = LoadImage(NULL, "res/Leafeye.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	pMaskRight = CreateBitmapMask(pBitmapRight, RGB(0, 0, 0), width_height[0], width_height[1]);
}

LeafEyeView::~LeafEyeView(void)
{
}

void LeafEyeView::Draw(HDC hDC, RECT rect, int xFrom, int xTo)
{
	if(!pWorld->Instance()->menu)
	{
		int x = pLeafEye->GetLocation()->X;
		int y = pLeafEye->GetLocation()->Y;
		int width = pLeafEye->GetLocation()->width;
		int height = pLeafEye->GetLocation()->height;
		int imageW = width_height[0];
		int imageH = width_height[1];
		int difWidth = (width - imageW) / 2;
		int difHeight = height - imageH;

		HDC bufDC = CreateCompatibleDC(hDC);
		if(this->pLeafEye->GetDirection() == Direction::Left)
			SelectObject(bufDC, pBitmapLeft);
		else
			SelectObject(bufDC, pBitmapRight);

		if(x + width >= xFrom && x <= xTo)
		{
			if(this->pLeafEye->GetDirection() == Direction::Left)
				BitBltTransparant(hDC, x + difWidth - xFrom, y + difHeight, imageW, imageH, bufDC, 0, 0, pBitmapLeft, pMaskLeft);
			else
				BitBltTransparant(hDC, x + difWidth - xFrom, y + difHeight, imageW, imageH, bufDC, 0, 0, pBitmapRight, pMaskRight);
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
			SelectObject(hDC, hPen);

			// draw the lines
			Polyline(hDC, leftOfPengy, 2);
			Polyline(hDC, bottomOfPengy, 2);
			Polyline(hDC, topOfPengy, 2);
			Polyline(hDC, rightOfPengy, 2);

			DeleteObject(hPen);
		}
#pragma endregion
	}	
}
