/** 
 * @file LogLevel.cpp
 * @author Mnsx_x <xx1527030652@gmail.com>
 * @date 2026/4/7
 * @description 
 */

#include "LogLevel.h"

#include <string>

namespace mnsx {

    std::string levelToString(LogLevel level) {

        switch (level) {
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO:  return "INFO";
            case LogLevel::WARN:  return "WARN";
            case LogLevel::ERROR: return "ERROR";
            case LogLevel::FATAL: return "FATAL";
            default:              return "UNKNOWN";
        }
    }
}
