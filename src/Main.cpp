#include <LibBase/Common.hpp>
#include <LibBase/Debug.hpp>
#include <LibC/stddef.h>
#include <LibC/stdint.h>
#include <LibC/stdio.h>
#include <Multiboot.h>

extern "C" void __cxa_pure_virtual() { PANIC("Pure virtual function called!"); }

#define CHECK_FLAG(flags, bit) ((flags) & (1 << (bit)))

extern "C" void kmain(uint32_t magic, uint32_t address) {
    kputs("Hello, world!\n");
    multiboot_info_t *mbi;

    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        PANIC("Invalid magic number!");
    }

    kprintf("magic = 0x%X\n", (unsigned)magic);

    mbi = (multiboot_info_t *)address;
    kprintf("flags = 0x%X\n", (unsigned)mbi->flags);

    if (CHECK_FLAG(mbi->flags, 0)) {
        kprintf("mem_lower = %uKB, mem_upper = %uKB\n",
                (unsigned)mbi->mem_lower, (unsigned)mbi->mem_upper);
    }
}
