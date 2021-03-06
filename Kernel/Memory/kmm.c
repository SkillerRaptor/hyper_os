#include <Kernel/Memory/kmm.h>

#include <string.h>
#include <Kernel/Memory/mm.h>
#include <Kernel/Memory/pmm.h>

#include <AK/logger.h>

typedef struct
{
	uint64_t pages;
	uint64_t size;
} heapheader_t;

void* kmalloc(size_t size)
{
	size_t page_count = (size + (PAGE_SIZE - 1)) / PAGE_SIZE;
	
	void* ptr = (uint8_t*)pmm_callocate_pages(page_count + 1);
	
	if (!ptr)
		return NULL;
	
	ptr += PHYSICAL_MEMORY_OFFSET;
	
	heapheader_t* metadata = (heapheader_t*)ptr;
	ptr += PAGE_SIZE;
	
	metadata->pages = page_count;
	metadata->size = size;
	
	return ptr;
}

void* kcalloc(size_t num, size_t size)
{
	void* ptr = kmalloc(num * size);
	memset(ptr, 0, num * size);
	return ptr;
}

void* krealloc(void* ptr, size_t size)
{
	if (!ptr)
		return kmalloc(size);
	
	heapheader_t* metadata = ptr - PAGE_SIZE;
	
	size_t current_size = (metadata->size + (PAGE_SIZE - 1)) / PAGE_SIZE;
	size_t new_size = (size + (PAGE_SIZE - 1)) / PAGE_SIZE;
	if (current_size == new_size)
	{
		metadata->size = new_size;
		return ptr;
	}
	
	void* new_ptr = kmalloc(new_size);
	if (new_ptr == NULL)
		return NULL;
	
	if (metadata->size > new_size)
		memcpy(new_ptr, ptr, new_size);
	else
		memcpy(new_ptr, ptr, metadata->size);
	
	kfree(ptr);
	
	return new_ptr;
}

void kfree(void* ptr)
{
	heapheader_t* metadata = ptr - PAGE_SIZE;
	pmm_free_pages((void*)metadata - PHYSICAL_MEMORY_OFFSET, metadata->pages + 1);
}