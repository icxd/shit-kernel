#pragma once

#define MAKE_NOT_COPYABLE(T)                                                   \
    T(const T &) = delete;                                                     \
    T &operator=(const T &) = delete

#define MAKE_NOT_MOVABLE(T)                                                    \
    T(T &&) = delete;                                                          \
    T &operator=(T &&) = delete
