/** 
 * @file BasicUsage.cpp
 * @author Mnsx_x <xx1527030652@gmail.com>
 * @date 2026/4/6
 * @description 
 */

#include <iostream>
#include <vector>

#include "LogBackend.h"
#include "Logger.h"

using namespace mnsx;

void stress_test(int id, int count) {
    for (int i = 0; i < count; ++i) {
        // 测试不同的日志级别
        if (i % 10 == 0) {
            LOG_ERROR << "Thread " << id << " found a critical issue at iteration: " << i;
        } else {
            LOG_INFO << "Thread " << id << " is processing task " << i << "... [Mnsx-KrakenPool integration pending]";
        }
    }
}

int main() {
    try {
        std::cout << "--- Mnsx-ArgusLog Day 1 Initialization ---" << std::endl;

        // 1. 初始化后端：创建一个名为 argus_test.log 的文件
        auto file_backend = std::make_shared<FileLogBackend>("argus_test.log");

        // 2. 注入全局后端
        mnsx::setGlobalLogBackend(file_backend);

        // 3. 单线程基础测试
        LOG_INFO << "Argus-eyed system is online.";
        LOG_DEBUG << "This is a debug message that should be aligned.";
        LOG_ERROR << "Test error: " << 404 << " - Not Found.";

        // 4. 多线程压力测试 (模拟 10 个线程同时写入)
        std::cout << "Starting multi-threaded stress test..." << std::endl;
        const int thread_count = 10;
        const int logs_per_thread = 100;
        std::vector<std::thread> threads;

        for (int i = 0; i < thread_count; ++i) {
            threads.emplace_back(stress_test, i, logs_per_thread);
        }

        for (auto& t : threads) {
            t.join();
        }

        std::cout << "Test completed. Please check 'argus_test.log' for results." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}