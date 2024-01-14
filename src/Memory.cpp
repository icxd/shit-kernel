#include <LibBase/Debug.hpp>
#include <Memory.hpp>

extern uint32_t end; // defined in linker.ld
uintptr_t kernel_end = (uintptr_t)&end;

namespace Memory {

// Memory map entry type names
static const char *MemoryMapEntryTypeNames[] = {
    "Usable",   "Reserved",     "ACPI Reclaimable",
    "ACPI NVS", "Bad Memory",   "Bootloader Reclaimable",
    "Kernel",   "Kernel Stack", "Page Tables",
    "Heap",     "Bootloader",   "Framebuffer",
};

// Memory map
MemoryMap *memory_map = nullptr;

// Memory map size
uint32_t memory_map_size = 0;

// Memory map entry count
uint32_t memory_map_entry_count = 0;

// Initialize memory
void initialize(multiboot_info_t *multiboot_info) {
    // Get memory map
    memory_map = (MemoryMap *)multiboot_info->mmap_addr;
    memory_map_size = multiboot_info->mmap_length;
    memory_map_entry_count = memory_map_size / sizeof(MemoryMapEntry);

    // Print memory map
    Logger::debug("Memory map:\n");
    for (uint32_t i = 0; i < memory_map_entry_count; i++) {
        MemoryMapEntry *entry = &memory_map->entries[i];
        Logger::debug("  %X %X %s\n", entry->base, entry->length,
                      MemoryMapEntryTypeNames[entry->type]);
    }
}

// Allocate memory
void *allocate(uint32_t size) {
    // Align size to 4 bytes
    size = (size + 3) & ~3;

    // Find a free memory region
    for (uint32_t i = 0; i < memory_map_entry_count; i++) {
        MemoryMapEntry *entry = &memory_map->entries[i];

        // Check if the region is usable
        if (entry->type != (uint32_t)MemoryMapEntryType::Usable) {
            continue;
        }

        // Check if the region is large enough
        if (entry->length < size) {
            continue;
        }

        // Allocate memory
        void *address = (void *)entry->base;
        entry->base += size;
        entry->length -= size;

        Logger::debug("Allocated %u bytes at 0x%X\n", size, address);

        return address;
    }

    // No memory region found
    PANIC("No memory region found\n");
    return nullptr;
}

} // namespace Memory