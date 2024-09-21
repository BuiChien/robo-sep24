#ifndef __ABSTRACT_STATE__
#define __ABSTRACT_STATE__
#include "Event.hpp"
#include "Document.hpp"

enum StateId : uint8_t
{
    kStartup
};

class IStateEventListener : public IEventListener
{
public:
    IStateEventListener() : IEventListener() {

    }
    virtual ~IStateEventListener() {

    }
    virtual void ChangeState(uint8_t stateId) = 0;
};

class AbstractState
{
public:
    AbstractState(uint8_t id);
    virtual ~AbstractState();
    void RegisterEventListener(IStateEventListener *const listener);
    void ProcessEvent(const Event *const event) const;
    virtual void Enter();
    virtual void Exit();
    virtual void Update();
    uint8_t GetId() const;
    void SetDocument(Document* const doc);
protected:
    void RaiseEvent(const Event* const event);
private:
    const uint8_t id_;
    IStateEventListener* listener_;
    Document* doc_;
};

#endif //__ABSTRACT_STATE__