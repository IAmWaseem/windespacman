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
	placeRect.left = Character::Instance()->GetLocation()->X - xFrom;
	placeRect.top = Character::Instance()->GetLocation()->Y;
	placeRect.right = placeRect.left + bitmap->Width();
	placeRect.bottom = placeRect.top + bitmap->Height();
	Character::Instance()->GetLocation()->width = bitmap->Width();
	Character::Instance()->GetLocation()->height = bitmap->Height();
	bitmap->TransparentPaint(hdc, RGB(46, 46, 46), &placeRect, NULL); 

	if(Renderer::ShowDebug)
	{
		ostringstream s;
		int x = Character::Instance()->GetLocation()->X;
		int y = Character::Instance()->GetLocation()->Y;
		s << "Location = ( " << x << ", " << y << " )";
		
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

		TextOut(hdc, 15, 35, character, strlen(character));
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


