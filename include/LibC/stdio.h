#ifndef LIBC_STDIO_H
#define LIBC_STDIO_H

#include <LibC/stdarg.h>
#include <LibC/stddef.h>
#include <LibC/stdint.h>

typedef struct {
    int level;       /* fill/empty level of buffer */
    uint32_t flags;  /* file status flags */
    char fd;         /* file descriptor */
    uint8_t hold;    /* ungetx char if no buffer */
    int bsize;       /* buffer size */
    uint8_t *buffer; /* data transfer buffer */
    uint8_t *curp;   /* current active pointer */
    uint32_t istemp; /* temporary file indicator */
    int16_t token;   /* used for validity checking */
} FILE;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;
#define stdin stdin
#define stdout stdout
#define stderr stderr

#define EOF (-1)

/* print formatted string */
int fprintf(FILE *, const char *, ...);
int printf(const char *, ...);
int snprintf(char *, size_t, const char *, ...);
int sprintf(char *, const char *, ...);
int vfprintf(FILE *, const char *, va_list);
int vprintf(const char *, va_list);
int vsnprintf(char *, size_t, const char *, va_list);
int vsprintf(char *, const char *, va_list);

#endif // LIBC_STDIO_H

