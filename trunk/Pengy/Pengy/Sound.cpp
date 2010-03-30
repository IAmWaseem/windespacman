//////////////////////////////////////////////////////////////////////////////////////////////////
//																								//
//  This version of Sound is using SDL. It's capable of playing background sound and			//
//	multiple sounds of events at the same time.													//
//																								//
//	To play sound such messages as below have to be sent.										//
//																								//
//	To start backround sound in a loop:															//
//	MessageQueue::Inst()->sendMessage(CM_SOUND_LOOP,(WPARAM)(LPCTSTR)"path here", 0);			//
//																								//
//	To end backround sound:																		//
//	MessageQueue::Inst()->sendMessage(CM_SOUND_END_LOOP, 0, 0);									//
//																								//
//	To play sound of an event:																	//
//	MessageQueue::Inst()->sendMessage(CM_SOUND_EVENT,(WPARAM)(LPCTSTR)"path here", n_of_times);	//
//																								//
//	n_of_times = integer how many sound shall be played ( 0 = play 1 time, 1 = 2 times ect. )	//
//																								//
//////////////////////////////////////////////////////////////////////////////////////////////////
#include "Sound.h"

Sound* Sound::pInstance = NULL;

Sound* Sound::Instance(){
	if(pInstance == NULL){
		pInstance = new Sound();
	}
	return pInstance;
}

Sound::Sound(void)
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	pMusic = NULL;
}

Sound::~Sound(void)
{
	Mix_FreeChunk(pEffect);
	Mix_FreeMusic(pMusic);
	Mix_CloseAudio();	
	if(pInstance != 0)delete pInstance;
}

void Sound::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch (message) 
	{
	case CM_SOUND_LOOP:
	 	pMusic = NULL;
 		pMusic = Mix_LoadMUS((const char *)wParam);
		if (Mix_PlayMusic(pMusic, -1) == -1)
		{
			break;
		}
		break;
	case CM_SOUND_END_LOOP:
		if(pMusic != NULL)
			Mix_FreeMusic(pMusic);
		break;
	case CM_SOUND_EVENT:
		pEffect = NULL;
		pEffect = Mix_LoadWAV((const char *)wParam);
		if(Mix_PlayChannel(-1, pEffect, lParam) == -1)
		{
			break;
		}
		break;
	}
}
