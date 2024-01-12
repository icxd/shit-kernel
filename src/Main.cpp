#include <LibBase/Common.hpp>
#include <LibBase/Debug.hpp>
#include <LibBase/Logger.hpp>
#include <LibC/stddef.h>
#include <LibC/stdint.h>
#include <LibC/stdio.h>
#include <Multiboot.h>

extern "C" void __cxa_pure_virtual() { PANIC("Pure virtual function called!"); }

#define CHECK_FLAG(flags, bit) ((flags) & (1 << (bit)))

extern "C" void kmain(uint32_t magic, uint32_t address) {
    Logger::info("Hello, world!");
    multiboot_info_t *mbi;

    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        PANIC("Invalid magic number: 0x%X\n", (unsigned)magic);
    }

    Logger::debug("magic = 0x%X", (unsigned)magic);

    mbi = (multiboot_info_t *)address;
    Logger::debug("flags = 0b%b", (unsigned)mbi->flags);

    if (CHECK_FLAG(mbi->flags, 0)) {
        Logger::debug("mem_lower = %uKB, mem_upper = %uKB",
                      (unsigned)mbi->mem_lower, (unsigned)mbi->mem_upper);
    }
}
