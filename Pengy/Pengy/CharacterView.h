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
		Jump,
		Sliding,
		Sliding2
	};

	void Update();
	void LoadImage(CharacterImage image, LPCSTR path);
	CharacterImage GetCurrentImage();
	void ChangeCurrentImage(CharacterImage image);
	void draw(HDC hdc);

private:
	map<CharacterImage, Bitmap*> * pImages;
	CharacterImage currentImage;
};
