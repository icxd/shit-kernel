#include <LibBase/Array.hpp>
#include <LibBase/Common.hpp>
#include <LibBase/Debug.hpp>
#include <LibBase/String.hpp>
#include <LibC/stddef.h>
#include <LibC/stdint.h>
#include <Serial.hpp>

void kputchar(char ch) {
    while ((port_byte_in(get_serial_log_port() + 5) & 0x20) == 0)
        ;
    port_byte_out(get_serial_log_port(), ch);
}

void kputs(const char *s) {
    for (int i = 0; s[i] != '\0'; i++)
        kputchar(s[i]);
}

static String to_string(size_t value, size_t base = 10, bool upper = false,
                        size_t width = 0) {
    VERIFY(base >= 2 && base <= 16);

    char buffer[65];
    size_t i = 0;
    do {
        size_t remainder = value % base;
        buffer[i++] = remainder < 10 ? remainder + '0'
                                     : remainder - 10 + (upper ? 'A' : 'a');
        value /= base;
    } while (value != 0);

    if (width > i) {
        for (size_t j = i; j < width; j++) {
            buffer[j] = '0';
        }
        i = width;
    }

    buffer[i] = '\0';

    for (size_t j = 0; j < i / 2; j++) {
        char tmp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = tmp;
    }

    return String{buffer};
}

// TODO: properly implement following: https://en.wikipedia.org/wiki/Printf
void kvprintf(const char *format, va_list ap) {
    for (size_t i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            switch (format[++i]) {
            case 'c': {
                char c = va_arg(ap, int);
                kputchar(c);
                break;
            }
            case 's': {
                const char *s = va_arg(ap, const char *);
                kputs(s);
                break;
            }
            case 'd': {
                int d = va_arg(ap, int);
                if (d < 0) {
                    kputchar('-');
                    d = -d;
                }
                kputs(to_string(d).c_str());
                break;
            }
            case 'u': {
                unsigned u = va_arg(ap, unsigned);
                kputs(to_string(u).c_str());
                break;
            }
            case 'x': {
                unsigned x = va_arg(ap, unsigned);
                kputs(to_string(x, 16, false, 8).c_str());
                break;
            }
            case 'X': {
                unsigned x = va_arg(ap, unsigned);
                kputs(to_string(x, 16, true, 8).c_str());
                break;
            }
            case 'p': {
                void *p = va_arg(ap, void *);
                kputs(to_string((size_t)p, 16, false, 8).c_str());
                break;
            }
            case '%': {
                kputchar('%');
                break;
            }
            default: {
                VERIFY_NOT_REACHED();
                break;
            }
            }
        } else {
            kputchar(format[i]);
        }
    }
}

void kprintf(const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    kvprintf(format, ap);
    va_end(ap);
}