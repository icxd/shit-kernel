#include <LibBase/Common.hpp>
#include <LibBase/Debug.hpp>
#include <LibBase/Logger.hpp>
#include <LibC/stddef.h>
#include <LibC/stdint.h>
#include <LibC/stdio.h>
#include <Memory.hpp>
#include <Multiboot.h>

extern "C" void __cxa_pure_virtual() { PANIC("Pure virtual function called!"); }

static const char *multiboot_flag_names[] = {
    "Memory",
    "Boot device",
    "Command line",
    "Modules",
    "Aout symbol table",
    "ELF sections",
    "Memory map",
    "Drive info",
    "Config table",
    "Boot loader name",
    "APM table",
    "VBE info",
    "Framebuffer info",
    "ELF symbols",
    "Memory info",
    "Multiboot info",
    "Mmap address",
    "Drives address",
    "Config table address",
    "Boot loader name address",
    "APM table address",
    "VBE info address",
    "Framebuffer info address",
    "Module address",
    "Kernel start address",
    "Kernel end address",
    "Multiboot header address",
};

extern "C" void kmain(uint32_t magic, uint32_t address) {
    Logger::debug("This is a debug message\n");
    Logger::info("This is an info message\n");
    Logger::warning("This is a warning message\n");
    Logger::error("This is an error message\n");
    Logger::fatal("This is a fatal message\n");

    Logger::info("Hello, world!\n");
    multiboot_info_t *mbi;

    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        PANIC("Invalid magic number: 0x%X\n", (unsigned)magic);
    }

    Logger::debug("Magic = 0x%X\n", (unsigned)magic);

    mbi = (multiboot_info_t *)address;
    Logger::debug("Flags = 0b%b\n", (unsigned)mbi->flags);
    for (int i = 0; i < 32; i++) {
        if (CHECK_FLAG(mbi->flags, i)) {
            Logger::debug("  %s\n", multiboot_flag_names[i]);
        }
    }

    if (CHECK_FLAG(mbi->flags, 0)) {
        Logger::debug("Lower memory = %uKB\n", (unsigned)mbi->mem_lower);
        Logger::debug("Upper memory = %uKB\n", (unsigned)mbi->mem_upper);
    }

    Memory::initialize(mbi);

    int *a = (int *)Memory::allocate(sizeof(int));
    *a = 42;
    Logger::info("a = %d\n", *a);
}
