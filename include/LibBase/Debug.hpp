#pragma once

#include <LibC/stdarg.h>
#include <LibC/stdint.h>
#include <LibIO/Ports.hpp>

// TODO: make dynamic based off of a enum
inline uint16_t get_serial_log_port() { return 0x3F8; }

void kputchar(char);
void kputs(const char *);
void kvprintf(const char *, va_list);
void kprintf(const char *, ...);

// TODO: template <typename... Args> void kprintf(const char *, Args...);