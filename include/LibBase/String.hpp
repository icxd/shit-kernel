#pragma once

#include <LibC/stddef.h>
#include <LibC/stdint.h>
#include <LibC/string.h>

class String {
  public:
    String(const char *str)
        : m_str(const_cast<char *>(str)), m_size(strlen(str)) {}
    String(const char *str, size_t size)
        : m_str(const_cast<char *>(str)), m_size(size) {}
    String(const String &other) : m_str(other.m_str), m_size(other.m_size) {}
    ~String() = default;

    String &operator=(const String &other) {
        m_str = other.m_str;
        m_size = other.m_size;
        return *this;
    }

    String substring(size_t start) const { return String(m_str + start); }
    String substring(size_t start, size_t end) const {
        return String(m_str + start, end - start);
    }

    char get(size_t index) const { return m_str[index]; }

    const char *c_str() const { return m_str; }
    size_t length() const { return m_size; }

  private:
    char *m_str;
    size_t m_size;
};

class StringBuilder {
  public:
    StringBuilder() : m_buffer(nullptr), m_size(0), m_capacity(0) {}
    ~StringBuilder() {
        if (m_buffer) delete[] m_buffer;
    }

    void append(const String &str) {
        ensure_capacity(m_size + str.length());
        memcpy(m_buffer + m_size, str.c_str(), str.length());
        m_size += str.length();
    }

    void append(uint64_t value) {
        char buffer[32];
        size_t size = 0;
        do {
            buffer[size++] = '0' + (value % 10);
            value /= 10;
        } while (value);
        ensure_capacity(m_size + size);
        for (size_t i = 0; i < size; i++) {
            m_buffer[m_size + i] = buffer[size - i - 1];
        }
        m_size += size;
    }

    String build() {
        ensure_capacity(m_size + 1);
        m_buffer[m_size] = '\0';
        return String(m_buffer);
    }

  private:
    void ensure_capacity(size_t capacity) {
        if (capacity <= m_capacity) return;
        size_t new_capacity = m_capacity * 2;
        if (new_capacity < capacity) new_capacity = capacity;
        char *new_buffer = new char[new_capacity];
        if (m_buffer) {
            memcpy(new_buffer, m_buffer, m_size);
            delete[] m_buffer;
        }
        m_buffer = new_buffer;
        m_capacity = new_capacity;
    }

    char *m_buffer;
    size_t m_size;
    size_t m_capacity;
};