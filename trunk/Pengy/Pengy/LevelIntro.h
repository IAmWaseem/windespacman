#pragma once
#include "Observer.h"
#include "LevelIntroView.h"

class LevelIntro : public Observer
{
public:
	LevelIntro(LPCSTR levelPicturePath, LPCSTR levelInfoPicturePath, int timeLevelPicture, int timeLevelInfoPicture);
	~LevelIntro(void);
	void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
private:
	LevelIntroView * view;
	int timeLevelPicture;
	int timeLevelInfoPicture;
	LPCSTR levelPicturePath;
	LPCSTR levelInfoPicturePath;
	int timeElapsed;
};
