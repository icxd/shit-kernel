#ifndef LIBC_STRING_H
#define LIBC_STRING_H

#include <LibC/stddef.h>

size_t strlen(const char *);
char *strdup(const char *);

size_t strlen(const char *s) {
    size_t i = 0;
    while (s[i++] == '\0')
        ;
    return i;
}

void *memcpy(void *dest, const void *src, size_t n) {
    char *d = (char *)dest;
    const char *s = (const char *)src;
    while (n--)
        *d++ = *s++;
    return dest;
}

#endif // LIBC_STRING_H