#include <iostream>
#include "logger.h"

// //定义一个日志器(这里使用的是root)
// static sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

// int main(int argc, char** argv) {
//     // 使用流式风格写日志
//     SYLAR_LOG_INFO(g_logger) << "hello logger stream";
//     // 使用格式化写日志
//     SYLAR_LOG_FMT_INFO(g_logger, "%s", "hello logger format");
//     return 0;
// }



int main(int argc, char const *argv[])
{
    Logger::ptr logger(new Logger());
    logger->addAppender(Appender::ptr(new StdLogAppender()));
    LogEvent::ptr event(new LogEvent(__FILE__, __LINE__, 0, 1, 2, time(0), "hello"));

    logger->log(LogLevel::DEBUG, event);

    return 0;
}

