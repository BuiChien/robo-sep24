#include "MemoryPool.hpp"
#define MAX_ITEMS (64)
#define MEM_ACCESS_TIMEOUT_MS (1000)

MemoryPool::MemoryPool(uint8_t itemSize, uint8_t numItem, uint8_t* const buffer)
	: item_size_(itemSize),
	number_item_(numItem),
	buffer_(buffer),
	alloc_status_(0),
	handle_(xSemaphoreCreateMutex())
{
	if (number_item_ > MAX_ITEMS)
	{
		configASSERT("Number of items is over maximum value!");
	}
}

MemoryPool::~MemoryPool()
{
}

void* MemoryPool::Alloc()
{
	void* alloc = nullptr;
	uint64_t mask = 0;
	xSemaphoreTake(handle_, pdMS_TO_TICKS(MEM_ACCESS_TIMEOUT_MS));
	for (size_t i = 0; i < number_item_; i++)
	{
		mask = static_cast<uint64_t>(1) << i;
		if (0 == (alloc_status_ & mask))
		{
			alloc = buffer_ + (i * item_size_);
			alloc_status_ |= mask;
			break;
		}
	}
	xSemaphoreGive(handle_);
	return alloc;
}

void MemoryPool::Free(void* addr)
{
	void* alloc = nullptr;
	xSemaphoreTake(handle_, pdMS_TO_TICKS(MEM_ACCESS_TIMEOUT_MS));
	for (size_t i = 0; i < number_item_; i++)
	{
		alloc = buffer_ + (i * item_size_);
		if (alloc == addr)
		{
			alloc = buffer_ + (i * item_size_);
			alloc_status_ &= ~(static_cast<uint64_t>(1) << i);
			break;
		}
	}
	xSemaphoreGive(handle_);
}
