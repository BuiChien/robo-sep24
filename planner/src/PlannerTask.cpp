#include <Global.hpp>
#include "PlannerTask.hpp"
#include "StateMachine.hpp"
#include "StartupState.hpp"

static StartupState startup_state;
static AbstractState* state_table[] = {
    &startup_state
};

PlannerTask::PlannerTask()
    : doc_(),
    state_machine_(state_table, sizeof(state_table) / sizeof(state_table[0]))
{
}

PlannerTask::~PlannerTask()
{
}

void PlannerTask::Init()
{
    state_machine_.Init();
}

void PlannerTask::SendToModule(const Event* const event)
{

}

void PlannerTask::Run()
{
    Event* event = nullptr;
    state_machine_.ChangeState(StateId::kStartup);
    for(;;) 
    {
        if(xQueueReceive(gPlannerQueueHandle, &event, portMAX_DELAY))
        {
            state_machine_.ProcessEvent(event);
            gEventPool->Free(event);
        } 
        else
        {
            state_machine_.Update();
        }
    }
}
