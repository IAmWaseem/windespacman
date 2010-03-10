#include "View.h"
#include "Renderer.h"

View::View()
{
}

View::~View()
{
}

void View::registerToGraphics()
{
	renderer->Inst()->attach(this);
}

void View::unRegisterToGraphics()
{
	renderer->Inst()->detach(this);
}

void View::Draw(HDC hDC, RECT rect, int xFrom, int xTo)
{
}
void View::BitBltTransparant(HDC hdc, int x, int y, int cx, int cy, HDC source, int x1, int y1, HANDLE image, HANDLE transparantMask)
{
	HANDLE oldHandle;

	oldHandle = SelectObject(source, transparantMask);
	BitBlt(hdc, x, y, cx, cy, source, x1, y1, SRCAND);

	SelectObject(source, image);	
	BitBlt(hdc, x, y, cx, cy, source, x1, y1, SRCPAINT);

	SelectObject(source, image);	
	SelectObject(source, oldHandle);
}

HANDLE View::CreateBitmapMask(HANDLE hbmColour, COLORREF crTransparent, int width, int height)
{
	HDC hdcMem, hdcMem2;
	HANDLE hbmMask;

	// Create monochrome (1 bit) mask bitmap.  
	hbmMask = CreateBitmap(width, height, 1, 1, NULL);

	// Get some HDCs that are compatible with the display driver

	hdcMem = CreateCompatibleDC(0);
	hdcMem2 = CreateCompatibleDC(0);

	SelectObject(hdcMem, hbmColour);
	SelectObject(hdcMem2, hbmMask);

	// Set the background colour of the colour image to the colour
	// you want to be transparent.
	SetBkColor(hdcMem, crTransparent);

	// Copy the bits from the colour image to the B+W mask... everything
	// with the background colour ends up white while everythig else ends up
	// black...Just what we wanted.

	BitBlt(hdcMem2, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY);

	// Take our new mask and use it to turn the transparent colour in our
	// original colour image to black so the transparency effect will
	// work right.
	BitBlt(hdcMem, 0, 0, width, height, hdcMem2, 0, 0, SRCINVERT);

	// Clean up.

	DeleteDC(hdcMem);
	DeleteDC(hdcMem2);

	return hbmMask;
}