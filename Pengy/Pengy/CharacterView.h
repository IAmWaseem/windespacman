#pragma once

#include "View.h"
#include "World.h"
#include <map>
#include <windows.h>

#include "Renderer.h"
#include <sstream>

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
	void LoadCVImage(CharacterImage image, LPCSTR path);
	CharacterImage GetCurrentImage();
	void ChangeCurrentImage(CharacterImage image);
	void Draw(HDC hdc, RECT rect, int xFrom, int xTo);

private:
	map<CharacterImage, HANDLE> * pImages;
	map<CharacterImage, HANDLE> * pMasks;
	map<CharacterImage, int*> * pWidthHeight;
	CharacterImage currentImage;
	World * world;
};
