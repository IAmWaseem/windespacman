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
    virtual void recieveMessage(UINT message)= 0;
    ~Observer();
};

