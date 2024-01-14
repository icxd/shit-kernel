#include <LibBase/Common.hpp>

[[noreturn]] void panic(const char *message, const char *file, uint32_t line,
                        ...) {
    asm volatile("cli");
    va_list ap;
    va_start(ap, line);
    Logger::fatal("%s:%d: ", file, line, message);
    kvprintf(message, ap);
    kprintf("\n");
    va_end(ap);

    while (1) {
        asm("hlt");
    }
}