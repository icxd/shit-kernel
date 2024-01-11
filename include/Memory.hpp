#pragma once

#include <LibC/stddef.h>
#include <LibC/stdint.h>

extern void *end;

uintptr_t placement_pointer = (uintptr_t)&end;
uintptr_t heap_end = (uintptr_t)NULL;

uint32_t *frames;
uint32_t nframes;

#define INDEX_FROM_BIT(b) ((b) / (0x20))
#define OFFSET_FROM_BIT(b) ((b) % (0x20))

void kmalloc_startat(uintptr_t);
uintptr_t kmalloc_real(size_t, int, uintptr_t);
uintptr_t kmalloc(size_t);

void set_frame(uintptr_t);
void clear_frame(uintptr_t);
uint32_t test_frame(uintptr_t);
uint32_t first_frame();
void alloc_frame(page_t *, int, int);
void dma_frame(page_t *, int, int, uintptr_t);
void free_frame(page_t *);

uintptr_t memory_used();
uintptr_t memory_total();

void paging_install(uint32_t);
void debug_print_directory();
void switch_page_directory(page_directory_t *);
page_t *get_page(uintptr_t, int, page_directory_t *);
void page_fault(registers_t *);

void heap_install();
void *sbrk(intptr_t);