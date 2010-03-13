#pragma once

#include "Observer.h"
#include "MessageQueue.h"
#include <SDL_mixer.h>


class Sound : public Observer
{
public:
	Mix_Music* pMusic;
	Mix_Chunk* pEffect;
	static Sound* Instance();
    ~Sound();
    void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
protected:
	Sound();
private:
	
	static Sound* pInstance;
	
};
