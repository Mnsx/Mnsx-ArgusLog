/** 
 * @file LogBackend.cpp
 * @author Mnsx_x <xx1527030652@gmail.com>
 * @date 2026/4/7
 * @description 日志处理类接口实现
 */

#include "LogBackend.h"

namespace mnsx {

    FileLogBackend::FileLogBackend(const std::string &file_path) {

        // 打开日志文件输出流
        this->file_stream_.open(file_path, std::ios::out | std::ios::app);
        if (this->file_stream_.is_open() == false) {
            throw std::runtime_error("Failed to open log file: " + file_path);
        }
    }

    FileLogBackend::~FileLogBackend() {
        this->file_stream_.close();
    }

    void FileLogBackend::append(const LogEvent &event) {
        std::string log_line = this->formatEvent(event);

        if (this->file_stream_.is_open() == true) {
            this->file_stream_ << log_line << "\n"; // 不能使用std::endl，因为endl会刷新磁盘，增加开销
        }
    }

    std::string FileLogBackend::formatEvent(const LogEvent &event) {

        // 处理时间数据
        auto time = std::chrono::system_clock::to_time_t(event.timestamp);
        struct tm local_time{};
        mnsx::safe_localtime(&time, &local_time);
        char buf[100];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &local_time);

        // 左对齐函数对象
        auto addRightSpace = [](const std::string& s, size_t width) {
            return s.length() < width ? s + std::string(width - s.length(), ' ') : s;
        };

        // 右对齐
        auto addLeftSpace = [](const std::string& s, size_t width) {
            return s.length() < width ? s + std::string(width - s.length(), ' ') : s;
        };

        // 处理线程编号
        std::string cur_thread_id = std::to_string(std::hash<std::thread::id>{}(event.thread_id) % 1000000);

        // 组装数据，并填充对齐
        std::string str = "[ " + static_cast<std::string>(buf) + " ] ";
        str.append("[ " + addRightSpace(mnsx::levelToString(event.level), 5) + " ] ");
        str.append("[ " + addLeftSpace(cur_thread_id, 8) + " ] ");
        str.append("[ " + addRightSpace(event.filename + ":" + std::to_string(event.line_number), 30) + " ] ");
        str.append(event.content);

        return str;
    }
}
