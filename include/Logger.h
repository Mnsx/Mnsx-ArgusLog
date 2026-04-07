/** 
 * @file Logger.h
 * @author Mnsx_x <xx1527030652@gmail.com>
 * @date 2026/4/7
 * @description 日志编写类的接口声明
 */
#ifndef ARGUSLOG_LOGGER_H
#define ARGUSLOG_LOGGER_H

#include <memory>
#include <sstream>

#include "LogLevel.h"

namespace mnsx {
    class LogBackend;

    /**
     * @brief 设置全局日志处理类
     * @param backend 日志处理类
     */
    void setGlobalLogBackend(std::shared_ptr<LogBackend> backend);

    /**
     * @brief 获取全局日志处理类
     * @return 智能指针管理的日志处理类
     */
    std::shared_ptr<LogBackend> getGlobalLogBackend();

    class Logger {
    public:
        /**
         * @brief 构造函数
         * @param level // 日志级别
         * @param file // 发出日志文件路径
         * @param line // 发出日志行数
         */
        Logger(LogLevel level, const char* file, int line);

        /**
         * @brief 析构函数
         */
        ~Logger();

        /**
         * @brief 返回字符串流，方便使用链式编程
         * @return 字符串流
         */
        std::stringstream& stream() {
            return this->stream_;
        }

    private:
        LogLevel level_; // 日志级别
        const char* file_; // 发出日志的路径
        int line_; // 发出日志的行数
        std::stringstream stream_; // 日志内容字符串流
    };
}

#define LOG_DEBUG mnsx::Logger(mnsx::LogLevel::DEBUG, __FILE__, __LINE__).stream()
#define LOG_INFO  mnsx::Logger(mnsx::LogLevel::INFO,  __FILE__, __LINE__).stream()
#define LOG_ERROR mnsx::Logger(mnsx::LogLevel::ERROR, __FILE__, __LINE__).stream()


#endif //ARGUSLOG_LOGGER_H