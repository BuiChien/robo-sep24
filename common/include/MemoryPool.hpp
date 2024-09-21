#ifndef __MEMORY_POOL__
#define __MEMORY_POOL__

#include <stdint.h>
#include <FreeRTOS.h>
#include <semphr.h>

class MemoryPool
{
public:
	MemoryPool(uint8_t itemSize, uint8_t numItem, uint8_t* const buffer);
	~MemoryPool();
	void* Alloc();
	void Free(void *addr);
private:
	const uint8_t item_size_;
	const uint8_t number_item_;
	uint8_t* const buffer_;
	uint64_t alloc_status_;
	SemaphoreHandle_t handle_;
};

#endif // !__MEMORY_POOL__

