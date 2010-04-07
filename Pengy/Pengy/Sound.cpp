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
	backgroundWPARAM = NULL;
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
		if(lParam == 1)
		{
			if(backgroundWPARAM != NULL)
				wParam = backgroundWPARAM;
		}
		else
		{
			backgroundWPARAM = wParam;
		}

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
