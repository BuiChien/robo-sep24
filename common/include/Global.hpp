#ifndef __GLOBAL__
#define __GLOBAL__
#include "MemoryPool.hpp"
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

extern QueueHandle_t gPlannerQueueHandle;
extern MemoryPool* const gEventPool;

#endif
