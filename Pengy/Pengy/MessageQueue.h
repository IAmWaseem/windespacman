#pragma once

#include <windows.h>
#include <vector>
using namespace std;

class Observer;

class MessageQueue
{
public:
    static MessageQueue* Instance();
    ~MessageQueue();

	void Attach( Observer *myObserver);
	void Detach( Observer *myObserver);
    void SendMessage(UINT message, WPARAM wParam, LPARAM lParam);

  protected:
    MessageQueue();
  private:
    static MessageQueue* pInstance;
	vector <Observer*> myObs;
};
