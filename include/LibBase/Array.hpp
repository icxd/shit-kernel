#pragma once

#include <LibBase/Common.hpp>
#include <LibC/stddef.h>

template <typename T, size_t N> class Array {
  public:
    constexpr Array() = default;
    constexpr Array(T data[N]) {
        for (size_t i = 0; i < N; i++) {
            m_data[i] = data[i];
        }
    }

    constexpr size_t size() const { return N; }
    constexpr bool is_empty() const { return N == 0; }

    constexpr T &operator[](size_t index) { return m_data[index]; }

    bool contains(const T &value) const {
        for (size_t i = 0; i < N; i++) {
            if (m_data[i] == value) {
                return true;
            }
        }
        return false;
    }

    void append(const T &value) {
        VERIFY(N < N + 1);
        m_data[N] = value;
    }

    constexpr T *begin() { return m_data; }
    constexpr T *end() { return m_data + N; }

  private:
    T m_data[N];
};