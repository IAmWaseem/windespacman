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

	enum DigitImage
	{
		d0,
		d1,
		d2,
		d3,
		d4,
		d5,
		d6,
		d7,
		d8,
		d9
	};

	void Update();
	void LoadCVImage(CharacterImage image, LPCSTR path);
	void LoadDigitImage(DigitImage image, LPCSTR path);
	CharacterImage GetCurrentImage();
	void ChangeCurrentImage(CharacterImage image);
	void Draw(HDC hdc, RECT rect, int xFrom, int xTo);
	void DrawHud(HDC hdc);

private:
	map<CharacterImage, HANDLE> * pImages;
	map<CharacterImage, HANDLE> * pMasks;
	map<DigitImage, HANDLE> * pDigitImages;
	map<DigitImage, HANDLE> * pDigitMasks;
	map<CharacterImage, int*> * pWidthHeight;
	HANDLE goldFishImage;
	HANDLE goldFishImageMask;
	HANDLE snowBallImage;
	HANDLE snowBallImageMask;
	HANDLE piranhaImage;
	HANDLE piranhaImageMask;
	HANDLE ladyBugImage;
	HANDLE ladyBugImageMask;
	HANDLE livesImage;
	HANDLE livesImageMask;
	HANDLE imageX;
	HANDLE imageXMask;
	
	int imageXWidth;
	int imageXHeight;
	int digitWidth;
	int digitHeight;
	int snowBallImageHeight;
	int snowBallImageWidth;
	int piranhaImageHeight;
	int piranhaImageWidth;
	int ladyBugImageHeight;
	int ladyBugImageWidth;
	int livesImageHeight;
	int livesImageWidth;
	int goldFishImageHeight;
	int goldFishImageWidth;

	CharacterImage currentImage;
	World * pWorld;

	void DrawRowFish(HDC hdc, int numFish);
	void DrawRowWeapons(HDC hdc, int numWeapons, HANDLE weaponImage, HANDLE weaponMask, int imageHeight, int imageWidth);
	void DrawRowLives(HDC hdc, int numLives);
};
