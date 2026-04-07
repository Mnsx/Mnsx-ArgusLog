/** 
 * @file Logger.cpp
 * @author Mnsx_x <xx1527030652@gmail.com>
 * @date 2026/4/7
 * @description 
 */

#include "Logger.h"

#include "LogBackend.h"
#include "LogEvent.h"

namespace mnsx {
    static std::shared_ptr<LogBackend> g_backend = nullptr;
    static std::mutex g_backend_mtx; // 保护后端切换的锁

    // 2. 实现 Setter
    void setGlobalLogBackend(std::shared_ptr<LogBackend> backend) {
        std::lock_guard<std::mutex> lock(g_backend_mtx);
        g_backend = std::move(backend); // 使用 move 减少一次引用计数操作
    }

    // 3. 实现 Getter
    std::shared_ptr<LogBackend> getGlobalLogBackend() {
        std::lock_guard<std::mutex> lock(g_backend_mtx);
        return g_backend;
    }

    Logger::Logger(LogLevel level, const char *file, int line)
        : level_(level), file_(file), line_(line) {}

    Logger::~Logger() {

        // 文本内容
        std::string content = this->stream_.str();

        // 包装日志
        LogEvent event(this->level_, this->file_, this->line_, std::move(content));

        // 将数据传到后端
        mnsx::getGlobalLogBackend().get()->append(event);
    }
}
