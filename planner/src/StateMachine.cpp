#include <Global.hpp>
#include "StateMachine.hpp"

StateMachine::StateMachine(AbstractState * const * stateTable, 
                uint8_t numberState)
    : state_table_(stateTable),
    number_state_(numberState),
    state_now_(nullptr),
    listener_(nullptr)
{

}

StateMachine::~StateMachine()
{
}

void StateMachine::Init()
{
    for (int i = 0; i < number_state_; i++)
    {
        state_table_[i]->RegisterEventListener(this);
    }
}

void StateMachine::ProcessEvent(const Event *const event) const
{
    if (state_now_ != nullptr)
    {
        state_now_->ProcessEvent(event);
    }
}

void StateMachine::Update()
{
    if (state_now_ != nullptr)
    {
        state_now_->Update();
    }
}

void StateMachine::ChangeState(uint8_t stateId)
{
    if(stateId < number_state_)
    {
        if (state_now_ != nullptr && state_now_->GetId() != stateId)
        {
            state_now_->Exit();
        }
        state_now_ = state_table_[stateId];
        state_now_->Enter();
    } 
    else
    {
        configASSERT("stateId is out of range!");
    }
}

void StateMachine::OnReceiveEventHandler(const Event *const event)
{
    if (listener_ != nullptr)
    {
        listener_->SendToModule(event);
    }
}

void StateMachine::RegisterListener(IStateMachineListener* const listener)
{
    listener_ = listener;
}
