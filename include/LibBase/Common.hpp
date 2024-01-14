#pragma once

#include <LibBase/Debug.hpp>
#include <LibBase/Logger.hpp>
#include <LibC/stdint.h>

#define PACKED __attribute__((packed))
#define ALIGNED(x) __attribute__((aligned(x)))
#define NORETURN __attribute__((noreturn))

#define UNUSED(x) (void)(x)

#define PANIC(msg, ...) panic(msg, __FILE__, __LINE__, ##__VA_ARGS__)

[[noreturn]] void panic(const char *message, const char *file, uint32_t line,
                        ...);

#define CHECK_FLAG(flags, bit) ((flags) & (1 << (bit)))

#define VERIFY_NOT_REACHED() PANIC("Execution reached unreachable code!")
#define VERIFY(expression)                                                     \
    if (!(expression)) PANIC("ASSERTION FAILED: " #expression)

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))