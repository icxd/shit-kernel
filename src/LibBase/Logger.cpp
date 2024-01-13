#include <LibBase/Logger.hpp>

void Logger::log(Severity severity, const char *message, va_list args,
                 bool prefix) {
    if (prefix) kprintf(" %s ", severity_to_string(severity));
    kvprintf(message, args);
}