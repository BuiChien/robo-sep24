#ifndef __PLANNER_TASK__
#define __PLANNER_TASK__
#include "Event.hpp"
#include "Document.hpp"
#include "StateMachine.hpp"

class PlannerTask : public IStateMachineListener
{
public:
    PlannerTask();
    ~PlannerTask();
    void Init();
    void SendToModule(const Event* const event) override;
    void Run();
private:
    Document doc_;
    StateMachine state_machine_;
};

#endif