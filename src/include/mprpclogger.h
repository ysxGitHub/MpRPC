#pragma once

#include <string>

#include "lockqueue.h"

#define LOG_INFO(logmsgFormat, ...)                       \
    do                                                    \
    {                                                     \
        Logger &logger = Logger::GetInstance();           \
        logger.SetLogLevel(INFO);                         \
        char buf[1024] = {0};                             \
        snprintf(buf, 1024, logmsgFormat, ##__VA_ARGS__); \
        logger.Log(buf);                                  \
    } while (0)

#define LOG_ERROR(logmsgFormat, ...)                      \
    do                                                    \
    {                                                     \
        Logger &logger = Logger::GetInstance();           \
        logger.SetLogLevel(ERROR);                        \
        char buf[1024] = {0};                             \
        snprintf(buf, 1024, logmsgFormat, ##__VA_ARGS__); \
        logger.Log(buf);                                  \
    } while (0)

#define LOG_FATAL(logmsgFormat, ...)                      \
    do                                                    \
    {                                                     \
        Logger &logger = Logger::GetInstance();           \
        logger.SetLogLevel(FATAL);                        \
        char buf[1024] = {0};                             \
        snprintf(buf, 1024, logmsgFormat, ##__VA_ARGS__); \
        logger.Log(buf);                                  \
        exit(-1);                                         \
    } while (0)

#ifdef MUDEBUG
#define LOG_DEBUG(logmsgFormat, ...)                      \
    do                                                    \
    {                                                     \
        Logger &logger = Logger::GetInstance();           \
        logger.SetLogLevel(DEBUG);                        \
        char buf[1024] = {0};                             \
        snprintf(buf, 1024, logmsgFormat, ##__VA_ARGS__); \
        logger.Log(buf);                                  \
    } while (0)
#else
#define LOG_DEBUG(logmsgFormat, ...)
#endif

// 定义日志级别
enum LogLevel
{
    INFO,  // 普通信息
    ERROR, // 错误信息
    FATAL, // core信息
    DEBUG, // 调试信息
};

// Mprpc框架提供的日志系统
class Logger
{
public:
    // 获取日志的单例
    static Logger &GetInstance();
    // 设置日志级别
    void SetLogLevel(LogLevel level);
    // 写日志
    void Log(std::string msg);

private:
    int logLevel_;                     // 记录日志级别
    LockQueue<std::string> lockQueue_; // 日志缓冲队列

    Logger();
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;
};
