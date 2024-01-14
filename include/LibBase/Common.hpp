#pragma once

#include <LibBase/Debug.hpp>
#include <LibC/stdint.h>

#define PANIC(msg, ...) panic(msg, __FILE__, __LINE__, ##__VA_ARGS__)

[[noreturn]] inline void panic(const char *message, const char *file,
                               uint32_t line, ...) {
    asm volatile("cli");
    va_list ap;
    va_start(ap, line);
    kprintf("PANIC(%s:%d): ", file, line, message);
    kvprintf(message, ap);
    va_end(ap);

    while (1) {
        asm("hlt");
    }
}

#define CHECK_FLAG(flags, bit) ((flags) & (1 << (bit)))

#define VERIFY_NOT_REACHED() PANIC("Execution reached unreachable code!")
#define VERIFY(expression)                                                     \
    if (!(expression)) PANIC("ASSERTION FAILED: " #expression)

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))