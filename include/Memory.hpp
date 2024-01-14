#pragma once

#include <LibBase/Common.hpp>
#include <LibBase/Debug.hpp>
#include <LibBase/Logger.hpp>
#include <LibC/stddef.h>
#include <LibC/stdint.h>
#include <Multiboot.h>

namespace Memory {

// Memory map entry
struct MemoryMapEntry {
    uint64_t base;
    uint64_t length;
    uint32_t type;
    uint32_t acpi_extended;
} PACKED;

// Memory map
struct MemoryMap {
    uint32_t size;
    MemoryMapEntry entries[0];
} PACKED;

// Memory map entry types
enum class MemoryMapEntryType {
    Usable = 1,
    Reserved = 2,
    ACPIReclaimable = 3,
    ACPINVS = 4,
    BadMemory = 5,
    BootloaderReclaimable = 0x1000,
    Kernel = 0x1001,
    KernelStack = 0x1002,
    PageTables = 0x1003,
    Heap = 0x1004,
    Bootloader = 0x1005,
    Framebuffer = 0x1006,
};

void initialize(multiboot_info_t *multiboot_info);
void *allocate(uint32_t size);

} // namespace Memory