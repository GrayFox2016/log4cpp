#ifndef __MACRO_H__
#define __MACRO_H__

// coroutineId haven't been finished

#define LOG(logger, level) \
    if(logger->getLevel() <= level) \
        LogEventWrap(LogEvent::ptr(new LogEvent(logger, level, \
                        __FILE__, __LINE__, 0, GetThreadId(),\
                GetCoroutineId(), time(0)))).getSS()

#define LOG_DEBUG(logger) LOG(logger, LogLevel::DEBUG)
#define LOG_INFO(logger) LOG(logger, LogLevel::INFO)
#define LOG_WARN(logger) LOG(logger, LogLevel::WARN)
#define LOG_ERROR(logger) LOG(logger, LogLevel::ERROR)
#define LOG_FATAL(logger) LOG(logger, LogLevel::FATAL)

// for format-style logs
#define FORMAT_LOG(logger, level, fmt, ...) \
    if(logger->getLevel() <= level) \
        LogEventWrap(LogEvent::ptr(new LogEvent(logger, level, \
                        __FILE__, __LINE__, 0, GetThreadId(),\
                GetCoroutineId(), time(0)))).getEvent()->format(fmt, __VA_ARGS__)

#define FORMAT_LOG_DEBUG(logger, fmt, ...) FORMAT_LOG(logger, LogLevel::DEBUG, fmt, __VA_ARGS__)
#define FORMAT_LOG_INFO(logger, fmt, ...)  FORMAT_LOG(logger, LogLevel::INFO, fmt, __VA_ARGS__)
#define FORMAT_LOG_WARN(logger, fmt, ...)  FORMAT_LOG(logger, LogLevel::WARN, fmt, __VA_ARGS__)
#define FORMAT_LOG_ERROR(logger, fmt, ...) FORMAT_LOG(logger, LogLevel::ERROR, fmt, __VA_ARGS__)
#define FORMAT_LOG_FATAL(logger, fmt, ...) FORMAT_LOG(logger, LogLevel::FATAL, fmt, __VA_ARGS__)






#endif //__MACRO_H__