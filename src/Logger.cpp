/** 
 * @file Logger.cpp
 * @author Mnsx_x <xx1527030652@gmail.com>
 * @date 2026/4/7
 * @description 日志编写类接口实现
 */

#include "Logger.h"

#include <cstring>

#include "LogBackend.h"
#include "LogEvent.h"

namespace mnsx {
    static std::shared_ptr<LogBackend> g_backend = nullptr; // 全局日志处理类
    static std::mutex g_backend_mtx; // 保护日志处理类切换的锁

    void setGlobalLogBackend(std::shared_ptr<LogBackend> backend) {
        std::lock_guard<std::mutex> lock(g_backend_mtx);
        g_backend = std::move(backend);
    }

    std::shared_ptr<LogBackend> getGlobalLogBackend() {
        std::lock_guard<std::mutex> lock(g_backend_mtx);
        return g_backend;
    }

    Logger::Logger(LogLevel level, const char *file, int line)
        : level_(level), line_(line) {

#ifdef PROJECT_ROOT_DIR
        const char* root = PROJECT_ROOT_DIR;
        size_t root_len = std::strlen(root);
        if (std::strncmp(file, root, root_len) == 0) {
            this->file_ = file + root_len;
        } else {
            this->file_ = file;
        }
#else
        this->file_ = file;
#endif
    }

    Logger::~Logger() {

        // 文本内容
        std::string content = this->stream_.str();

        // 包装日志
        LogEvent event(this->level_, this->file_, this->line_, std::move(content));

        // 将数据传到后端
        mnsx::getGlobalLogBackend().get()->append(event);
    }
}
