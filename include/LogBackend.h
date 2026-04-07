/** 
 * @file LogBackend.h
 * @author Mnsx_x <xx1527030652@gmail.com>
 * @date 2026/4/7
 * @description 
 */
#ifndef ARGUSLOG_LOGBACKEND_H
#define ARGUSLOG_LOGBACKEND_H

#include <fstream>
#include <mutex>

#include "LogEvent.h"

namespace mnsx {
    /**
     * 根据系统获取当前时间，线程安全
     * @param time_ptr time_t对象
     * @param result 返回值指针
     */
    inline static void safe_localtime(const time_t *time_ptr, struct tm *result) {
#if defined(_WIN32) || defined(_WIN64)
        localtime_s(result, time_ptr); // 调用win的localtime_s
#else
        localtime_r(time_ptr, result); // 调用linux的localtime_r
#endif
    }

    class LogBackend {
    public:
        virtual ~LogBackend() = default;
        virtual void append(const LogEvent& event) = 0;
    };

    class FileLogBackend : public LogBackend {
    public:
        explicit FileLogBackend(const std::string& file_path);
        ~FileLogBackend() override;

        void append(const LogEvent& event) override;

    private:
        std::ofstream file_stream_;
        std::mutex mtx_;

        std::string formatEvent(const LogEvent& event);
    };
}

#endif //ARGUSLOG_LOGBACKEND_H