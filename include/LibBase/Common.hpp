#pragma once

#include <LibBase/Debug.hpp>
#include <LibC/stdint.h>

#define PANIC(msg) panic(msg, __FILE__, __LINE__)

[[noreturn]] inline void panic(const char *message, const char *file,
                               uint32_t line) {
    asm volatile("cli");
    kprintf("PANIC(%s:%d): %s\n", file, line, message);
    while (1) {
        asm("hlt");
    }
}

#define VERIFY_NOT_REACHED() PANIC("Execution reached unreachable code!")
#define VERIFY(expression)                                                     \
    if (!(expression)) PANIC("ASSERTION FAILED: " #expression)

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))