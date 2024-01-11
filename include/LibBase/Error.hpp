#pragma once

#include <LibBase/Common.hpp>
#include <LibBase/Format.hpp>
#include <LibBase/Macros.hpp>
#include <LibC/stddef.h>

class Error {
  public:
    Error() : m_errno(0) {}
    Error(size_t errno) : m_errno(errno) {}
    Error(const Error &other) : m_errno(other.m_errno) {}
    ~Error() = default;

    Error &operator=(const Error &other) {
        m_errno = other.m_errno;
        return *this;
    }

    size_t errno() const { return m_errno; }

  private:
    size_t m_errno;
};

template <typename T> class ErrorOr {
  public:
    ErrorOr(T value) : m_is_error(false), m_value(value) {}
    ErrorOr(Error error) : m_is_error(true), m_error(error) {}
    ~ErrorOr() = default;

    bool is_error() const { return m_is_error; }
    T value() const { return m_value; }
    Error error() const { return m_error; }

    T unwrap() const {
        if (m_is_error) PANIC("ErrorOr::unwrap() called on ErrorOr with error");
        return m_value;
    }

    T unwrap_or(T default_value) const {
        return m_is_error ? default_value : m_value;
    }

    T unwrap_or_else(T (*f)()) const { return m_is_error ? f() : m_value; }

  private:
    bool m_is_error;
    T m_value;
    Error m_error;
};

template <> class ErrorOr<void> {
  public:
    ErrorOr() : m_is_error(false) {}
    ErrorOr(Error error) : m_is_error(true), m_error(error) {}
    ~ErrorOr() = default;

    bool is_error() const { return m_is_error; }
    Error error() const { return m_error; }

    void unwrap() const {
        if (m_is_error) PANIC("ErrorOr::unwrap() called on ErrorOr with error");
    }

    void unwrap_or_else(void (*f)()) const {
        if (m_is_error) f();
    }

  private:
    bool m_is_error;
    Error m_error;
};

#define TRY(expr)                                                              \
    ({                                                                         \
        auto __val = (expr);                                                   \
        if (__val.is_error()) {                                                \
            return __val.error();                                              \
        }                                                                      \
        __val.value();                                                         \
    })