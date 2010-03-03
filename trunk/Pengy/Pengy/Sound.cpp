//////////////////////////////////////////////////////////////////////////////////////////////
//																							//
//  This version of Sound is only capable of playing one sound at the time, thus next		//
//  version is still in progress - it will use some external libraries.						//
//																							//
//	To play sound such message as below has to be sent.										//
//																							//
//  MessageQueue::Inst()->sendMessage(CM_SOUND_EVENT,(WPARAM)(LPCTSTR)"res/pengy.wav", 0);	//
//																							//
//////////////////////////////////////////////////////////////////////////////////////////////
#include "Sound.h"

Sound* Sound::pInstance = NULL;

Sound* Sound::Inst(){
  if(pInstance == NULL){
    pInstance = new Sound();
  }
  return pInstance;
}

Sound::Sound(void)
{
}

Sound::~Sound(void)
{
	if(pInstance != 0)delete pInstance;
}

void Sound::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch (message) 
	{
	case CM_SOUND_LOOP:
		PlaySound((LPCTSTR)wParam, NULL, SND_NOSTOP|SND_FILENAME|SND_ASYNC|SND_LOOP);
		break;
	case CM_SOUND_END_LOOP:
		PlaySound(NULL, NULL, NULL);
		break;
	case CM_SOUND_EVENT:
		PlaySound((LPCTSTR)wParam, NULL, SND_NOSTOP|SND_FILENAME|SND_ASYNC);
		break;
	}
}
