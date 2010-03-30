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
	void DrawHud(HDC hdc);

private:
	map<CharacterImage, HANDLE> * pImages;
	map<CharacterImage, HANDLE> * pMasks;
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
	HANDLE image0;
	HANDLE image0Mask;
	HANDLE image1;
	HANDLE image1Mask;
	HANDLE image2;
	HANDLE image2Mask;
	HANDLE image3;
	HANDLE image3Mask;
	HANDLE image4;
	HANDLE image4Mask;
	HANDLE image5;
	HANDLE image5Mask;
	HANDLE image6;
	HANDLE image6Mask;
	HANDLE image7;
	HANDLE image7Mask;
	HANDLE image8;
	HANDLE image8Mask;
	HANDLE image9;
	HANDLE image9Mask;

	int imageXWidth;
	int imageXHeight;
	int imageWidth;
	int imageHeight;
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
