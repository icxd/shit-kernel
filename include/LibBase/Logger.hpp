#pragma once

#include <LibBase/Common.hpp>
#include <LibBase/Debug.hpp>
#include <LibC/stddef.h>

class Logger {
  public:
    enum class Severity {
        Debug,
        Info,
        Warning,
        Error,
        Fatal,
    };

    static void log(Severity severity, const char *message, va_list args);

    static void debug(const char *message, ...) {
#if defined(DEBUG)
        va_list args;
        va_start(args, message);
        log(Severity::Debug, message, args);
        va_end(args);
#else
        UNUSED(message);
#endif // defined(DEBUG)
    }

    static void info(const char *message, ...) {
        va_list args;
        va_start(args, message);
        log(Severity::Info, message, args);
        va_end(args);
    }

    static void warning(const char *message, ...) {
        va_list args;
        va_start(args, message);
        log(Severity::Warning, message, args);
        va_end(args);
    }

    static void error(const char *message, ...) {
        va_list args;
        va_start(args, message);
        log(Severity::Error, message, args);
        va_end(args);
    }

    static void fatal(const char *message, ...) {
        va_list args;
        va_start(args, message);
        log(Severity::Fatal, message, args);
        va_end(args);
    }
};

inline const char *severity_to_string(Logger::Severity severity) {
    switch (severity) {
    case Logger::Severity::Debug:
        return "\033[1;94m  [DEBUG]\033[0m"; // Blue
    case Logger::Severity::Info:
        return "\033[1;92m   [INFO]\033[0m"; // Green
    case Logger::Severity::Warning:
        return "\033[1;93m[WARNING]\033[0m"; // Yellow
    case Logger::Severity::Error:
        return "\033[1;91m  [ERROR]\033[0m"; // Red
    case Logger::Severity::Fatal:
        return "\033[1;95m  [FATAL]\033[0m"; // Magenta
    default:
        return "\033[1;91m[UNKNOWN]\033[0m"; // Red
    }
}
