#include <Global.hpp>
#include "Kernel.hpp"
#include "PlannerTask.hpp"
#include "ComIfTask.hpp"

constexpr uint16_t PLANNER_TASK_STACK_SIZE		= 128;
constexpr uint8_t  PLANNER_TASK_TASK_PRIORITY	= 1;
constexpr uint8_t  PLANNER_TASK_QUEUE_SIZE		= 16;
constexpr uint8_t  EVENT_MEMORY_POOL			= 32;
constexpr uint16_t COM_IF_TASK_STACK_SIZE		= 128;
constexpr uint8_t  COM_IF_TASK_TASK_PRIORITY	= 2;

static TaskHandle_t planner_task_;
static TaskHandle_t com_if_task_;
static uint8_t event_pool_memory_buffer[EVENT_MEMORY_POOL];
static MemoryPool event_pool_(sizeof(Event), EVENT_MEMORY_POOL, &event_pool_memory_buffer[0]);

QueueHandle_t gPlannerQueueHandle;
MemoryPool* const gEventPool = &event_pool_;

static void PlannerTaskFunc(void* arg)
{
	PlannerTask planner;
	planner.Init();
	planner.Run();
}

static void ComIfTaskFunc(void* arg)
{
	ComIfTask com_if;
	com_if.Init();
	com_if.Run();
}

static void KernelInitQueue()
{
	gPlannerQueueHandle = xQueueCreate(PLANNER_TASK_QUEUE_SIZE, sizeof(Event*));
}

static void KernelInitTask()
{
	xTaskCreate(PlannerTaskFunc, "PlannerTaskFunc", PLANNER_TASK_STACK_SIZE, nullptr, PLANNER_TASK_TASK_PRIORITY, &planner_task_);
	xTaskCreate(ComIfTaskFunc, "ComIfTaskFunc", COM_IF_TASK_STACK_SIZE, nullptr, COM_IF_TASK_TASK_PRIORITY, &com_if_task_);
}

void KernelInit() 
{
	KernelInitQueue();
	KernelInitTask();
	vTaskStartScheduler();
}