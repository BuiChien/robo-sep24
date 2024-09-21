#include  <Global.hpp>
#include "ComIfTask.hpp"

ComIfTask::ComIfTask()
{
}

ComIfTask::~ComIfTask()
{
}

void ComIfTask::Init()
{

}

void ComIfTask::Run()
{
	for (;;) 
	{
		vTaskDelay(1000);
	}
}
