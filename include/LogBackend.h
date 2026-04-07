/** 
 * @file LogBackend.h
 * @author Mnsx_x <xx1527030652@gmail.com>
 * @date 2026/4/7
 * @description 日志处理类接口声明
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
        /**
         * @brief 析构函数
         */
        virtual ~LogBackend() = default;

        /**
         * @brief 将日志事件存储，纯虚函数
         * @param event LogEvent结构体
         */
        virtual void append(const LogEvent& event) = 0;
    };

    /**
     * @brief 日志处理类的子类，将日志事件存储到文件中
     */
    class FileLogBackend : public LogBackend {
    public:
        /**
         * @brief 构造函数
         * @param file_path 文件路径
         */
        explicit FileLogBackend(const std::string& file_path);

        /**
         * @brief 析构函数
         */
        ~FileLogBackend() override;

        /**
         * @brief 将日志事件写入文件中
         * @param event 日志事件对象
         */
        void append(const LogEvent& event) override;

    private:
        std::ofstream file_stream_; // 文件输出流
        std::mutex mtx_; // 互斥锁

        /**
         * @brief 将日志事件对象转换为字符串
         * @param event 日志事件对象
         * @return 格式化的字符串
         */
        std::string formatEvent(const LogEvent& event);
    };
}

#endif //ARGUSLOG_LOGBACKEND_H