#pragma once

#include <vector>
using namespace std;

class Observer;

class MessageQueue
{
public:
    static MessageQueue* Inst();
    ~MessageQueue();

	void attach( Observer *myObserver);
	void detach( Observer *myObserver);
    void sendMessage(string message);

  protected:
    MessageQueue();
  private:
    static MessageQueue* pInstance;
	vector <Observer*> myObs;
};
