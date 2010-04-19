#include "MessageQueue.h"
#include "Observer.h"

MessageQueue* MessageQueue::pInstance = NULL;

MessageQueue* MessageQueue::Instance(){
  if(pInstance == NULL){
    pInstance = new MessageQueue();
  }
  return pInstance;
}

MessageQueue::MessageQueue(){ 
}

MessageQueue::~MessageQueue(){
  if(pInstance != 0)delete pInstance;
}

void MessageQueue::Attach( Observer *myObserver)
{
    myObs.push_back( myObserver);
}

void MessageQueue::Detach( Observer *myObserver)
{
    for (unsigned int i= 0; i< myObs.size(); i++)
    {
        if (myObs[i]== myObserver)
        {
            myObs.erase(myObs.begin()+i);
            return;
        }
    }
}

void MessageQueue::SendMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
    for (unsigned int i= 0; i< myObs.size(); i++)
    {
        myObs[i]->ReceiveMessage(message, wParam, lParam);
    }
}