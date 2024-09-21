#ifndef __EVENT__
#define __EVENT__
#include <stdint.h>

typedef struct Event_
{
    uint8_t id;
    union
    {
        
    } data;
} Event;

class IEventListener
{
public:
    IEventListener() {

    }
    virtual ~IEventListener() {

    }
    virtual void OnReceiveEventHandler(const Event *const event) = 0;
};

#endif //__EVENT__