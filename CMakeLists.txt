cmake_minimum_required(VERSION 3.10)
project(ArgusLog LANGUAGES CXX)

# 全局设置
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexec-charset=UTF-8")

# 定义核心库
add_library(ArgusLog STATIC
        src/Logger.cpp
        src/LogBackend.cpp
        src/LogLevel.cpp
)

# 配置库的头文件路径
include_directories(ArgusLog PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 添加宏到编译器
target_compile_definitions(ArgusLog PRIVATE PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")

# 定义实例程序
add_executable(ArgusDemo examples/BasicUsage.cpp)

# 建立连接关系
target_link_libraries(ArgusDemo PRIVATE ArgusLog)