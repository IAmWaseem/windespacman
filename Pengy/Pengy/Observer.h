#pragma once

#include <string>
using namespace std;

class MessageQueue;

class Observer
{
public:
    Observer();
    virtual void recieveMessage(string message)= 0;
    ~Observer();
};

