#pragma once

#include <windows.h>
#include "messages.h"
#include <string>
using namespace std;

class MessageQueue;

class Observer
{
public:
    Observer();
    virtual void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam)= 0;
    ~Observer();
protected:
	bool isPaused;
};

