/** 
 * @file Logger.h
 * @author Mnsx_x <xx1527030652@gmail.com>
 * @date 2026/4/7
 * @description 
 */
#ifndef ARGUSLOG_LOGGER_H
#define ARGUSLOG_LOGGER_H

#include <memory>
#include <sstream>

#include "LogLevel.h"

namespace mnsx {
    class LogBackend;

        void setGlobalLogBackend(std::shared_ptr<LogBackend> backend);
        std::shared_ptr<LogBackend> getGlobalLogBackend();

    class Logger {
    public:
        Logger(LogLevel level, const char* file, int line);
        ~Logger();

        std::stringstream& stream() {
            return this->stream_;
        }

    private:
        LogLevel level_;
        const char* file_;
        int line_;
        std::stringstream stream_;
    };
}

#define LOG_DEBUG mnsx::Logger(mnsx::LogLevel::DEBUG, __FILE__, __LINE__).stream()
#define LOG_INFO  mnsx::Logger(mnsx::LogLevel::INFO,  __FILE__, __LINE__).stream()
#define LOG_ERROR mnsx::Logger(mnsx::LogLevel::ERROR, __FILE__, __LINE__).stream()


#endif //ARGUSLOG_LOGGER_H