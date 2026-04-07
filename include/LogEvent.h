/** 
 * @file LogEvent.h
 * @author Mnsx_x <xx1527030652@gmail.com>
 * @date 2026/4/7
 * @description 
 */
#ifndef ARGUSLOG_LOGEVENT_H
#define ARGUSLOG_LOGEVENT_H

#include <thread>

#include "LogLevel.h"

namespace mnsx {

    struct LogEvent {
        LogLevel level;
        std::string filename;
        int line_number;
        std::thread::id thread_id;
        std::chrono::system_clock::time_point timestamp;
        std::string content;

        LogEvent(LogLevel level, std::string file, int line, std::string msg)
            : level(level), filename(std::move(file)), line_number(line),
            thread_id(std::this_thread::get_id()),
            timestamp(std::chrono::system_clock::now()),
            content(std::move(msg)) {}
    };
}

#endif //ARGUSLOG_LOGEVENT_H