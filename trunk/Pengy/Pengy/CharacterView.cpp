#include "CharacterView.h"
#include "Character.h"

CharacterView::CharacterView(void)
{
	pImages = new map<CharacterImage, Bitmap*>();
}

CharacterView::~CharacterView(void)
{

}

void CharacterView::Draw(HDC hdc, HWND m_hWnd)
{
	Bitmap * bitmap = pImages->find(currentImage)->second;
	RECT placeRect;
	placeRect.left = Character::Instance()->GetLocationX();
	placeRect.top = Character::Instance()->GetLocationY();
	placeRect.right = placeRect.left + bitmap->Width();
	placeRect.bottom = placeRect.top + bitmap->Height();
	Character::Instance()->SetHeight(bitmap->Height());
	Character::Instance()->SetWidth(bitmap->Width());
	bitmap->TransparentPaint(hdc, RGB(46, 46, 46), &placeRect, NULL); 
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


