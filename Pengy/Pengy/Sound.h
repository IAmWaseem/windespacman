#pragma once

#include "Observer.h"
#include "MessageQueue.h"
//#include <stdlib.h>
#include "SDL_mixer.h"
//#include "SDL_mixer.h"

class Sound : public Observer
{
public:
	Mix_Music* pMusic;
	Mix_Chunk* pEffect;
	WPARAM backgroundWPARAM;
	static Sound* Instance();
    ~Sound();
    void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
protected:
	Sound();
private:
	
	static Sound* pInstance;
	
};
