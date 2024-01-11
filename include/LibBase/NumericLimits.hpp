#pragma once

#include <LibC/stddef.h>
#include <LibC/stdint.h>

template <typename T> struct NumericLimits {};

template <> struct NumericLimits<size_t> {
    static constexpr size_t min() { return 0; }
    static constexpr size_t max() { return UINT64_MAX; }
    static constexpr bool is_signed() { return false; }
};