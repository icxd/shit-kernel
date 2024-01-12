#ifndef LIBC_STDDEF_H
#define LIBC_STDDEF_H

// TODO: upgrade to x64
#if defined(__i386__)
typedef int ptrdiff_t;
typedef unsigned int size_t;
#elif defined(__x86_64__)
typedef long ptrdiff_t;
typedef unsigned long size_t;
#endif // __i386__

#define NULL ((void *)0)

#endif // LIBC_STDDEF_H
