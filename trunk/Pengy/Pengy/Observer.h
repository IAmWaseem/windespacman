class MessageQueue;

class Observer
{
public:
    Observer(void);
    virtual void update( MessageQueue *messageQueue)= 0;
    ~Observer(void);
};

