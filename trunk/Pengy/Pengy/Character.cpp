#include "Character.h"
#include "CharacterView.h"
#include <iostream>
using namespace std;

Character* Character::pInstance = NULL;

Character::Character(void)
{
	locationX = 700;
	locationY = 350;
	width = 0;
	height = 0;
	characterStateMachine = new CharacterStateMachine();
}

Character::~Character(void)
{
}

void Character::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	ULONGLONG timeElapsed;
	switch (message) 
	{
	case CM_LEVEL_START:
		characterView = new CharacterView();
		characterView->LoadImage(CharacterView::CharacterImage::Left, "res/PengyAutumnLeft2.bmp");
		characterView->ChangeCurrentImage(CharacterView::CharacterImage::Left);
		characterView->registerToGraphics();
		break;

	case CM_UPDATE:
		timeElapsed = wParam;
		characterStateMachine->Update(timeElapsed);
		break;

	case CM_CHARACTER_SPACEBAR:
		characterStateMachine->Spacebar();
		break;

	case CM_CHARACTER_UP:
		characterStateMachine->Up();
		break;

	case CM_CHARACTER_DOWN:
		characterStateMachine->Down();
		break;

	case CM_CHARACTER_LEFT:
		characterStateMachine->Left();
		break;

	case CM_CHARACTER_RIGHT:
		characterStateMachine->Right();
		break;
	}
}

Character* Character::Instance()
{
	if(pInstance == NULL){
		pInstance = new Character();
	}
	return pInstance;
}

void Character::Update()
{

}

int Character::GetLocationX()
{
	return locationX;
}

int Character::GetLocationY()
{
	return locationY;
}

void Character::SetLocationX(int x)
{
	locationX = x;
}

void Character::SetLocationY(int y)
{
	locationY = y;
}

int Character::GetWidth()
{
	return width;
}

int Character::GetHeight()
{
	return height;
}

void Character::SetWidth(int width)
{
	this->width = width;
}

void Character::SetHeight(int height)
{
	this->height = height;
}
