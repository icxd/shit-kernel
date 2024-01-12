#pragma once

#include <LibC/stddef.h>
#include <LibC/stdint.h>

template <typename T> struct NumericLimits {};

template <> struct NumericLimits<size_t> {
    static constexpr size_t min() { return 0; }
    static constexpr size_t max() {
        if constexpr (sizeof(size_t) == sizeof(uint32_t)) return UINT32_MAX;
        else if constexpr (sizeof(size_t) == sizeof(uint64_t))
            return UINT64_MAX;
        else return 0;
    }
    static constexpr bool is_signed() { return false; }
};