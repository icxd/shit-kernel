#include <LibBase/Debug.hpp>
#include <Memory.hpp>

extern uint32_t end; // defined in linker.ld
uintptr_t kernel_end = (uintptr_t)&end;

namespace Memory {

void init(multiboot_info_t *mbi) {
    Logger::debug("end = 0x%X\n", (unsigned)kernel_end);
    Logger::debug("Kernel size = %u\n", (unsigned)kernel_end);
}

} // namespace Memory