#pragma once

#include <LibC/stddef.h>
#include <LibC/stdint.h>

#define PAGE_SIZE 4096
#define PAGE_ALIGN(x) ((x) + PAGE_SIZE - ((x) % PAGE_SIZE))

extern void *kernel_end;

void init_memory();
void *alloc_page();
void free_page(void *ptr);
void *alloc_pages(size_t count);
void free_pages(void *ptr, size_t count);

void *operator new(size_t size);
void *operator new[](size_t size);
void operator delete(void *p);
void operator delete[](void *p);

void *kmalloc(size_t size);
void *kmalloc_aligned(size_t size, size_t alignment);
void *krealloc(void *ptr, size_t size);
void kfree(void *ptr);