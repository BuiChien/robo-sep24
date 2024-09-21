#ifndef __STATE_MACHINE__
#define __STATE_MACHINE__
#include "Event.hpp"
#include "AbstractState.hpp"

class IStateMachineListener
{
public:
    ~IStateMachineListener() {}
    virtual void SendToModule(const Event* const event) = 0;
};

class StateMachine : public IStateEventListener
{
public:
    StateMachine(AbstractState * const * stateTable, 
                uint8_t numberState);
    ~StateMachine();
    void Init();
    void ProcessEvent(const Event *const event) const;
    void Update();
    void ChangeState(uint8_t stateId) override;
    void OnReceiveEventHandler(const Event *const event) override;
    void RegisterListener(IStateMachineListener* const listener);
private:
    AbstractState* const* state_table_;
    const uint8_t number_state_;
    AbstractState* state_now_;
    IStateMachineListener* listener_;
};

#endif