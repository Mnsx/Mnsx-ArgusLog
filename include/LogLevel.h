/** 
 * @file LogLevel.h
 * @author Mnsx_x <xx1527030652@gmail.com>
 * @date 2026/4/7
 * @description 
 */
#ifndef ARGUSLOG_LOGLEVEL_H
#define ARGUSLOG_LOGLEVEL_H
#include <string>

namespace mnsx {

    enum class LogLevel {
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL
    };

    std::string levelToString(LogLevel level);
}

#endif //ARGUSLOG_LOGLEVEL_H