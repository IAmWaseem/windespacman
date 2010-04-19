#include "LevelIntro.h"
#include "Skeleton.h"

LevelIntro::LevelIntro(LPCSTR levelPicturePath, LPCSTR levelInfoPicturePath, int timeLevelPicture, int timeLevelInfoPicture)
{
	this->timeLevelPicture = timeLevelPicture;
	this->timeLevelInfoPicture = timeLevelInfoPicture;
	this->levelPicturePath = levelPicturePath;
	this->levelInfoPicturePath = levelInfoPicturePath;
	this->timeElapsed = 0;
	view = new LevelIntroView(levelPicturePath, levelInfoPicturePath);
	view->RegisterToGraphics();
	MessageQueue::Instance()->SendMessage(CM_RENDERER_ONLY_DRAW_THIS, (int)((View*)view), NULL);
	MessageQueue::Instance()->Attach(this);
}

LevelIntro::~LevelIntro(void)
{
	MessageQueue::Instance()->Detach(this);
	MessageQueue::Instance()->SendMessage(CM_UNPAUSE, NULL, NULL);
	MessageQueue::Instance()->SendMessage(CM_RENDERER_NORMAL_RENDER, NULL, NULL);
	view->UnRegisterToGraphics();
	delete view;
	CSkeleton::paused = false;
}

void LevelIntro::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	int timeElapsed;
	switch(message)
	{
	case CM_UPDATE:
		timeElapsed = (int)wParam;
		this->timeElapsed += timeElapsed;
		if(this->timeElapsed >= timeLevelPicture && this->timeElapsed < timeLevelInfoPicture + timeLevelPicture)
			view->NextPicture();
		if(this->timeElapsed >= timeLevelPicture && this->timeElapsed >= timeLevelInfoPicture + timeLevelPicture)
			delete this;
		break;
	}
}
