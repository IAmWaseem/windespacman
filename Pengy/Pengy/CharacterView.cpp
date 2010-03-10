#include "CharacterView.h"
#include "Character.h"
#include "Bitmap.h"

CharacterView::CharacterView(void)
{
	pImages = new map<CharacterImage, HANDLE>();
	pMasks = new map<CharacterImage, HANDLE>();
	pWidthHeight = new map<CharacterImage, int*>();
}

CharacterView::~CharacterView(void)
{

}

void CharacterView::Draw(HDC hdc, RECT rect, int xFrom, int xTo)
{
	HANDLE bitmap = pImages->find(currentImage)->second;
	HANDLE mask = pMasks->find(currentImage)->second;
	int* wh = pWidthHeight->find(currentImage)->second;
	
	HDC bufDC = CreateCompatibleDC(hdc);
	SelectObject(bufDC, bitmap);

	int x = Character::Instance()->GetLocation()->X - xFrom;
	int y = Character::Instance()->GetLocation()->Y;
	int width = Character::Instance()->GetLocation()->width;
	int height = Character::Instance()->GetLocation()->height;
	int imageW = wh[0];
	int imageH = wh[1];

	int difWidth = (width - imageW) / 2;
	int difHeight = height - imageH;

	BitBltTransparant(hdc, x + difWidth, y + difHeight, imageW, imageH, bufDC, 0, 0, bitmap, mask);

	DeleteDC(bufDC);

#pragma region debug
	if(Renderer::ShowDebug)
	{
		ostringstream s;
		ostringstream s2;
		int x = (float)(Character::Instance()->GetLocation()->X);
		int y = (float)(Character::Instance()->GetLocation()->Y);
		int width = (float)(Character::Instance()->GetLocation()->width);
		int height = (float)(Character::Instance()->GetLocation()->height);
		s << "Location = ( " << x << ", " << y << " )";
		s2 << "Location = ( " << (int)(x / 64) << ", " << (int)(y / 64) << " )";
		
		LPCSTR PengyDirection = "";
		if(Character::Instance()->getDirection() == Direction::Left)
			PengyDirection = "left";
		else
			PengyDirection = "right";

		s << " & direction = " << PengyDirection;
		
		// cast to c_string
		LPCSTR character = "";
		string temp; 
		temp = s.str();
		character = temp.c_str();

		LPCSTR character2 = "";
		string temp2; 
		temp2 = s2.str();
		character2 = temp2.c_str();

		TextOut(hdc, 15, 35, character, strlen(character));

		TextOut(hdc, 15, 55, character2, strlen(character2));
		
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
	}
#pragma endregion
}

void CharacterView::Update()
{

}

void CharacterView::LoadCVImage(CharacterImage image, LPCSTR path)
{
	Bitmap * b = new Bitmap();
	b->LoadDIBFile(path);
	int width = b->Width();
	int height = b->Height();
	b->~Bitmap();	

	HANDLE bitmap;
	bitmap = LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);	
	pImages->insert(make_pair(image, bitmap));

	HANDLE mask;
	mask = CreateBitmapMask(bitmap, RGB(46, 46, 46), 200, 200);
	pMasks->insert(make_pair(image, mask));

	int* widthheight = new int[2]; widthheight[0] = width; widthheight[1] = height;
	pWidthHeight->insert(make_pair(image, widthheight));
}

CharacterView::CharacterImage CharacterView::GetCurrentImage()
{
	return currentImage;
}

void CharacterView::ChangeCurrentImage(CharacterImage image)
{
	currentImage = image;
}
