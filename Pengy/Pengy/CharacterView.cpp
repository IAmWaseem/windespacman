#include "CharacterView.h"
#include "Character.h"
#include "Bitmap.h"

CharacterView::CharacterView(void)
{
	pImages = new map<CharacterImage, HANDLE>();
	pMasks = new map<CharacterImage, HANDLE>();
	pWidthHeight = new map<CharacterImage, int*>();
	Bitmap * bitmap = new Bitmap();

	snowBallImage = LoadImage(NULL, "res/GadgetSnowball.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bitmap->LoadDIBFile("res/GadgetSnowball.bmp");
	snowBallImageHeight = bitmap->Height();
	snowBallImageWidth = bitmap->Width();
	snowBallImageMask = CreateBitmapMask(snowBallImage, RGB(0,0,0), snowBallImageWidth, snowBallImageHeight);

	goldFishImage = LoadImage(NULL, "res/GadgetGoldFish.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bitmap->DeleteObject();
	bitmap->LoadDIBFile("res/GadgetGoldFish.bmp");
	goldFishImageHeight = bitmap->Height();
	goldFishImageWidth = bitmap->Width();
	goldFishImageMask = CreateBitmapMask(goldFishImage, RGB(0,0,0), goldFishImageWidth, goldFishImageHeight);

	piranhaImage = LoadImage(NULL, "res/GadgetPiranha.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bitmap->DeleteObject();
	bitmap->LoadDIBFile("res/GadgetPiranha.bmp");
	piranhaImageHeight = bitmap->Height();
	piranhaImageWidth = bitmap->Width();
	piranhaImageMask = CreateBitmapMask(piranhaImage, RGB(0,0,0), piranhaImageWidth, piranhaImageHeight);

	ladyBugImage = LoadImage(NULL, "res/hudLadyBug.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bitmap->DeleteObject();
	bitmap->LoadDIBFile("res/hudLadyBug.bmp");
	ladyBugImageHeight = bitmap->Height();
	ladyBugImageWidth = bitmap->Width();
	ladyBugImageMask = CreateBitmapMask(ladyBugImage, RGB(0,0,0), ladyBugImageWidth, ladyBugImageHeight);

	livesImage = LoadImage(NULL, "res/GadgetExtraLife.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bitmap->DeleteObject();
	bitmap->LoadDIBFile("res/GadgetExtraLife.bmp");
	livesImageHeight = bitmap->Height();
	livesImageWidth = bitmap->Width();
	livesImageMask = CreateBitmapMask(livesImage, RGB(0,0,0), livesImageWidth, livesImageHeight);

	imageX = LoadImage(NULL, "res/hudX.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bitmap->DeleteObject();
	bitmap->LoadDIBFile("res/hudX.bmp");
	imageXHeight = bitmap->Height();
	imageXWidth = bitmap->Width();
	imageXMask = CreateBitmapMask(imageX, RGB(0,0,0), imageXWidth, imageXHeight);

	image0 = LoadImage(NULL, "res/number0.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bitmap->DeleteObject();
	bitmap->LoadDIBFile("res/number0.bmp");
	imageHeight = bitmap->Height();
	imageWidth = bitmap->Width();
	image0Mask = CreateBitmapMask(image0, RGB(0,0,0), imageWidth, imageHeight);

	image1 = LoadImage(NULL, "res/number1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	image1Mask = CreateBitmapMask(image1, RGB(0,0,0), imageWidth, imageHeight);

	image2 = LoadImage(NULL, "res/number2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	image2Mask = CreateBitmapMask(image2, RGB(0,0,0), imageWidth, imageHeight);

	image3 = LoadImage(NULL, "res/number3.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	image3Mask = CreateBitmapMask(image3, RGB(0,0,0), imageWidth, imageHeight);

	image4 = LoadImage(NULL, "res/number4.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	image4Mask = CreateBitmapMask(image4, RGB(0,0,0), imageWidth, imageHeight);

	image5 = LoadImage(NULL, "res/number5.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	image5Mask = CreateBitmapMask(image5, RGB(0,0,0), imageWidth, imageHeight);

	image6 = LoadImage(NULL, "res/number6.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	image6Mask = CreateBitmapMask(image6, RGB(0,0,0), imageWidth, imageHeight);

	image7 = LoadImage(NULL, "res/number7.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	image7Mask = CreateBitmapMask(image7, RGB(0,0,0), imageWidth, imageHeight);

	image8 = LoadImage(NULL, "res/number8.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	image8Mask = CreateBitmapMask(image8, RGB(0,0,0), imageWidth, imageHeight);

	image9 = LoadImage(NULL, "res/number9.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	image9Mask = CreateBitmapMask(image9, RGB(0,0,0), imageWidth, imageHeight);

}

CharacterView::~CharacterView(void)
{
	delete pImages;
	delete pMasks;
	delete pWidthHeight;
}

void CharacterView::Draw(HDC hdc, RECT rect, int xFrom, int xTo)
{
	if(!pWorld->Instance()->menu)
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
			DrawHud(hdc);
			DeleteDC(bufDC);
		
	
	ostringstream weaponPickedUp;
	weaponPickedUp << "Weapons: " << Character::Instance()->GetPickedWeapons();
	LPCSTR weapon = "";
	string temp; 
	temp = weaponPickedUp.str();
	weapon = temp.c_str();
	TextOut(hdc, 15, 75, weapon, strlen(weapon));

	ostringstream fishPickedUp;
	fishPickedUp << "Fish: " << Character::Instance()->GetPickedGoldFish();
	LPCSTR fish = "";
	string temp2; 
	temp2 = fishPickedUp.str();
	fish = temp2.c_str();
	TextOut(hdc, 15, 95, fish, strlen(fish));

	ostringstream lives;
	lives << "Lives: " << Character::Instance()->GetAmountLives();
	LPCSTR livesLeft = "";
	string temp3; 
	temp3 = lives.str();
	livesLeft = temp3.c_str();
	TextOut(hdc, 15, 115, livesLeft, strlen(livesLeft));		

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
		if(Character::Instance()->GetDirection() == Direction::Left)
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

		DeleteObject(hPen);
	}
#pragma endregion
	}
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

void CharacterView::DrawHud(HDC hdc)
{
	int lives = Character::Instance()->GetAmountLives();
	int fish = Character::Instance()->GetPickedGoldFish();
	int weapons = Character::Instance()->GetPickedWeapons();

	HANDLE weapon;
	HANDLE weaponMask;
	int weaponHeight;
	int weaponWidth;

	switch(Character::Instance()->GetWeaponType())
	{
	case GadgetView::GadgetImage::Piranha:
		weapon = piranhaImage;
		weaponMask = piranhaImageMask;
		weaponHeight = piranhaImageHeight;
		weaponWidth = piranhaImageWidth;
		break;
	case GadgetView::GadgetImage::Ladybug:
		weapon = ladyBugImage;
		weaponMask = ladyBugImageMask;
		weaponHeight = ladyBugImageHeight;
		weaponWidth = ladyBugImageWidth;
		break;
	case GadgetView::GadgetImage::SnowBall:
		weapon = snowBallImage;
		weaponMask = snowBallImageMask;
		weaponHeight = snowBallImageHeight;
		weaponWidth = snowBallImageWidth;
		break;
	}
	DrawRowFish(hdc, fish);
	DrawRowWeapons(hdc, weapons, weapon, weaponMask, weaponHeight, weaponWidth);
	DrawRowLives(hdc, lives);
}

void CharacterView::DrawRowFish(HDC hdc, int numFish)
{
	
	int numDigits = 1;
	if(numFish > 9)
	{
		numDigits = 2;
		if(numFish > 99)
			numDigits = 3;
	}
	int secondDigit = numFish % 10;
	int firstDigit = numFish / 10;

	int startX = 1000 - (2 * imageWidth) - goldFishImageWidth - imageXWidth;

	HDC bufDC = CreateCompatibleDC(hdc);
	SelectObject(bufDC, goldFishImage);
	BitBltTransparant(hdc, startX, 10, goldFishImageWidth, goldFishImageHeight, bufDC, 0, 0, goldFishImage, goldFishImageMask);
	DeleteDC(bufDC);
	
	startX += goldFishImageWidth;
	bufDC = CreateCompatibleDC(hdc);
	SelectObject(bufDC, imageX);
	BitBltTransparant(hdc, startX, 10, imageXWidth, imageXHeight, bufDC, 0, 0, imageX, imageXMask);
	DeleteDC(bufDC);

	startX += imageXWidth;

	if(numDigits == 2)
	{
		HANDLE digitImage;
		HANDLE digitMask;
		switch(firstDigit)
		{
		case 0:
			digitImage = image0;
			digitMask = image0Mask;
			break;
		case 1:
			digitImage = image1;
			digitMask = image1Mask;
			break;
		case 2:
			digitImage = image2;
			digitMask = image2Mask;
			break;
		case 3:
			digitImage = image3;
			digitMask = image3Mask;
			break;
		case 4:
			digitImage = image4;
			digitMask = image4Mask;
			break;
		case 5:
			digitImage = image5;
			digitMask = image5Mask;
			break;
		case 6:
			digitImage = image6;
			digitMask = image6Mask;
			break;
		case 7:
			digitImage = image7;
			digitMask = image7Mask;
			break;
		case 8:
			digitImage = image8;
			digitMask = image8Mask;
			break;
		case 9:
			digitImage = image9;
			digitMask = image9Mask;
			break;
		}
		bufDC = CreateCompatibleDC(hdc);
		SelectObject(bufDC, digitImage);
		BitBltTransparant(hdc, startX, 10, imageWidth, imageHeight, bufDC, 0, 0, digitImage, digitMask);
		DeleteDC(bufDC);
	}
	
	startX += imageWidth;

	HANDLE digitImage;
	HANDLE digitMask;
	switch(secondDigit)
	{
	case 0:
		digitImage = image0;
		digitMask = image0Mask;
		break;
	case 1:
		digitImage = image1;
		digitMask = image1Mask;
		break;
	case 2:
		digitImage = image2;
		digitMask = image2Mask;
		break;
	case 3:
		digitImage = image3;
		digitMask = image3Mask;
		break;
	case 4:
		digitImage = image4;
		digitMask = image4Mask;
		break;
	case 5:
		digitImage = image5;
		digitMask = image5Mask;
		break;
	case 6:
		digitImage = image6;
		digitMask = image6Mask;
		break;
	case 7:
		digitImage = image7;
		digitMask = image7Mask;
		break;
	case 8:
		digitImage = image8;
		digitMask = image8Mask;
		break;
	case 9:
		digitImage = image9;
		digitMask = image9Mask;
		break;
	}
	bufDC = CreateCompatibleDC(hdc);
	SelectObject(bufDC, digitImage);
	BitBltTransparant(hdc, startX, 10, imageWidth, imageHeight, bufDC, 0, 0, digitImage, digitMask);
	DeleteDC(bufDC);
}

void CharacterView::DrawRowWeapons(HDC hdc, int numWeapons, HANDLE weaponImage, HANDLE weaponMask, int imageHeight, int imageWidth)
{
		
	int numDigits = 1;
	if(numWeapons > 9)
	{
		numDigits = 2;
		if(numWeapons > 99)
			numDigits = 3;
	}
	int secondDigit = numWeapons % 10;
	int firstDigit = numWeapons / 10;

	int startX = 1000 - (2 * this->imageWidth) - imageWidth - imageXWidth;

	HDC bufDC = CreateCompatibleDC(hdc);
	SelectObject(bufDC, goldFishImage);
	BitBltTransparant(hdc, startX, 50, imageWidth, imageHeight, bufDC, 0, 0, weaponImage, weaponMask);
	DeleteDC(bufDC);
	
	startX += imageWidth;

	bufDC = CreateCompatibleDC(hdc);
	SelectObject(bufDC, imageX);
	BitBltTransparant(hdc, startX, 50, imageXWidth, imageXHeight, bufDC, 0, 0, imageX, imageXMask);
	DeleteDC(bufDC);

	startX += imageXWidth;

	if(numDigits == 2)
	{
		HANDLE digitImage;
		HANDLE digitMask;
		switch(firstDigit)
		{
		case 0:
			digitImage = image0;
			digitMask = image0Mask;
			break;
		case 1:
			digitImage = image1;
			digitMask = image1Mask;
			break;
		case 2:
			digitImage = image2;
			digitMask = image2Mask;
			break;
		case 3:
			digitImage = image3;
			digitMask = image3Mask;
			break;
		case 4:
			digitImage = image4;
			digitMask = image4Mask;
			break;
		case 5:
			digitImage = image5;
			digitMask = image5Mask;
			break;
		case 6:
			digitImage = image6;
			digitMask = image6Mask;
			break;
		case 7:
			digitImage = image7;
			digitMask = image7Mask;
			break;
		case 8:
			digitImage = image8;
			digitMask = image8Mask;
			break;
		case 9:
			digitImage = image9;
			digitMask = image9Mask;
			break;
		}
		bufDC = CreateCompatibleDC(hdc);
		SelectObject(bufDC, digitImage);
		BitBltTransparant(hdc, startX, 50, this->imageWidth, this->imageHeight, bufDC, 0, 0, digitImage, digitMask);
		DeleteDC(bufDC);
	}
	
	startX += this->imageWidth;

	HANDLE digitImage;
	HANDLE digitMask;
	switch(secondDigit)
	{
	case 0:
		digitImage = image0;
		digitMask = image0Mask;
		break;
	case 1:
		digitImage = image1;
		digitMask = image1Mask;
		break;
	case 2:
		digitImage = image2;
		digitMask = image2Mask;
		break;
	case 3:
		digitImage = image3;
		digitMask = image3Mask;
		break;
	case 4:
		digitImage = image4;
		digitMask = image4Mask;
		break;
	case 5:
		digitImage = image5;
		digitMask = image5Mask;
		break;
	case 6:
		digitImage = image6;
		digitMask = image6Mask;
		break;
	case 7:
		digitImage = image7;
		digitMask = image7Mask;
		break;
	case 8:
		digitImage = image8;
		digitMask = image8Mask;
		break;
	case 9:
		digitImage = image9;
		digitMask = image9Mask;
		break;
	}
	bufDC = CreateCompatibleDC(hdc);
	SelectObject(bufDC, digitImage);
	BitBltTransparant(hdc, startX, 50, this->imageWidth, this->imageHeight, bufDC, 0, 0, digitImage, digitMask);
	DeleteDC(bufDC);
}

void CharacterView::DrawRowLives(HDC hdc, int numLives)
{
	int numDigits = 1;
	if(numLives > 9)
	{
		numDigits = 2;
		if(numLives > 99)
			numDigits = 3;
	}
	int secondDigit = numLives % 10;
	int firstDigit = numLives / 10;

	int startX = 1000 - (2 * this->imageWidth) - livesImageWidth - imageXWidth;

	HDC bufDC = CreateCompatibleDC(hdc);
	SelectObject(bufDC, livesImage);
	BitBltTransparant(hdc, startX, 90, livesImageWidth, livesImageHeight, bufDC, 0, 0, livesImage, livesImageMask);
	DeleteDC(bufDC);
	
	startX += livesImageWidth;

	bufDC = CreateCompatibleDC(hdc);
	SelectObject(bufDC, imageX);
	BitBltTransparant(hdc, startX, 110, imageXWidth, imageXHeight, bufDC, 0, 0, imageX, imageXMask);
	DeleteDC(bufDC);

	startX += imageXWidth;

	if(numDigits == 2)
	{
		HANDLE digitImage;
		HANDLE digitMask;
		switch(firstDigit)
		{
		case 0:
			digitImage = image0;
			digitMask = image0Mask;
			break;
		case 1:
			digitImage = image1;
			digitMask = image1Mask;
			break;
		case 2:
			digitImage = image2;
			digitMask = image2Mask;
			break;
		case 3:
			digitImage = image3;
			digitMask = image3Mask;
			break;
		case 4:
			digitImage = image4;
			digitMask = image4Mask;
			break;
		case 5:
			digitImage = image5;
			digitMask = image5Mask;
			break;
		case 6:
			digitImage = image6;
			digitMask = image6Mask;
			break;
		case 7:
			digitImage = image7;
			digitMask = image7Mask;
			break;
		case 8:
			digitImage = image8;
			digitMask = image8Mask;
			break;
		case 9:
			digitImage = image9;
			digitMask = image9Mask;
			break;
		}
		bufDC = CreateCompatibleDC(hdc);
		SelectObject(bufDC, digitImage);
		BitBltTransparant(hdc, startX, 110, this->imageWidth, this->imageHeight, bufDC, 0, 0, digitImage, digitMask);
		DeleteDC(bufDC);
	}
	
	startX += this->imageWidth;

	HANDLE digitImage;
	HANDLE digitMask;
	switch(secondDigit)
	{
	case 0:
		digitImage = image0;
		digitMask = image0Mask;
		break;
	case 1:
		digitImage = image1;
		digitMask = image1Mask;
		break;
	case 2:
		digitImage = image2;
		digitMask = image2Mask;
		break;
	case 3:
		digitImage = image3;
		digitMask = image3Mask;
		break;
	case 4:
		digitImage = image4;
		digitMask = image4Mask;
		break;
	case 5:
		digitImage = image5;
		digitMask = image5Mask;
		break;
	case 6:
		digitImage = image6;
		digitMask = image6Mask;
		break;
	case 7:
		digitImage = image7;
		digitMask = image7Mask;
		break;
	case 8:
		digitImage = image8;
		digitMask = image8Mask;
		break;
	case 9:
		digitImage = image9;
		digitMask = image9Mask;
		break;
	}
	bufDC = CreateCompatibleDC(hdc);
	SelectObject(bufDC, digitImage);
	BitBltTransparant(hdc, startX, 110, this->imageWidth, this->imageHeight, bufDC, 0, 0, digitImage, digitMask);
	DeleteDC(bufDC);
}

