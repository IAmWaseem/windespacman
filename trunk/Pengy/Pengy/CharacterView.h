#pragma once
#include <map>
#include "Windows.h"
#include "Bitmap.h"
#include "View.h"
using namespace std;
using namespace dotnetguy;

class CharacterView : public View
{
public:
	CharacterView(void);
	~CharacterView(void);

	enum CharacterImage
	{
		Left,
		Left2,
		Right,
		Right2,
		Climb,
		Climb2,
		JumpLeft,
		JumpRight,
		Sliding,
		Sliding2,
		FallingLeft,
		FallingRight
	};

	void Update();
	void LoadImage(CharacterImage image, LPCSTR path);
	CharacterImage GetCurrentImage();
	void ChangeCurrentImage(CharacterImage image);
	void Draw(HDC hdc, int xFrom, int xTo);

private:
	map<CharacterImage, Bitmap*> * pImages;
	CharacterImage currentImage;
};
