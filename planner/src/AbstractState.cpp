#include "AbstractState.hpp"

AbstractState::AbstractState(uint8_t id)
    : id_(id),
    listener_(nullptr),
    doc_(nullptr)
{
}

AbstractState::~AbstractState()
{
}

void AbstractState::RegisterEventListener(IStateEventListener *const listener)
{
    listener_ = listener;
}

void AbstractState::ProcessEvent(const Event *const event) const
{
}

void AbstractState::Enter()
{
}

void AbstractState::Exit()
{
}

void AbstractState::Update()
{
}

uint8_t AbstractState::GetId() const
{
    return id_;
}

void AbstractState::SetDocument(Document* const doc)
{
    doc_ = doc;
}

void AbstractState::RaiseEvent(const Event* const event)
{
    if (listener_ != nullptr)
    {
        listener_->OnReceiveEventHandler(event);
    }
}
