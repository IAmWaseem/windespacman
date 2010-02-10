pragma once
#include "Observer.h"
#include "MessageQueue.h"

class Level : public Observer
{
public:
    Level(void);
    void update( MessageQueue *messageQueue);
public:
    ~Level(void);
};
