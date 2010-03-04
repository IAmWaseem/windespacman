#include "CharacterView.h"
#include "Character.h"

CharacterView::CharacterView(void)
{
	pImages = new map<CharacterImage, Bitmap*>();
}

CharacterView::~CharacterView(void)
{

}

void CharacterView::Draw(HDC hdc, int xFrom, int xTo)
{
	Bitmap * bitmap = pImages->find(currentImage)->second;
	RECT placeRect;
	placeRect.left = (long)((Character::Instance()->GetLocation()->X - xFrom) - 0.5*(bitmap->Width() - Character::Instance()->GetLocation()->width));
	placeRect.top = (long)((Character::Instance()->GetLocation()->Y) - 0.5*(bitmap->Height() - Character::Instance()->GetLocation()->height) + 5);
	placeRect.right = placeRect.left + bitmap->Width();
	placeRect.bottom = placeRect.top + bitmap->Height();
	bitmap->TransparentPaint(hdc, RGB(46, 46, 46), &placeRect, NULL); 

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
}

void CharacterView::Update()
{

}

void CharacterView::LoadImage(CharacterImage image, LPCSTR path)
{
	Bitmap * bitmap = new Bitmap();
	bitmap->LoadDIBFile(path);
	pImages->insert(make_pair(image, bitmap));
}

CharacterView::CharacterImage CharacterView::GetCurrentImage()
{
	return currentImage;
}

void CharacterView::ChangeCurrentImage(CharacterImage image)
{
	currentImage = image;
}
