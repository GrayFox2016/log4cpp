#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <memory>
#include <list>
#include <sstream>
#include <vector>
#include <iostream>
#include <ostream>
#include <map>
#include <fstream>
#include <stdarg.h>

#include "util.h"

// for stream-style logs
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


class Logger;

class LogLevel {
public:
    enum Level {
        UNKNOW = 0,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL
    };

    static const char* ToString(LogLevel::Level level);
    
    // static LogLevel::Level FromString(const std::string& str);
};




class LogEvent {
public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent(std::shared_ptr<Logger> logger,
            LogLevel::Level level, 
            const char* file, 
            int32_t line, 
            uint32_t elapse, 
            uint32_t threadId, 
            uint32_t coroutineId, 
            uint64_t timestamp
            );

    const char* getFile() const { return _file;}
    int32_t getLine() const { return _line;}
    uint32_t getElapse() const { return _elapse;}
    uint32_t getThreadId() const { return _threadId;}
    uint32_t getCoroutineId() const { return _coroutineId;}
    uint64_t getTime() const { return _timestamp;}
    std::string getContent() const { return _ss.str();}
    std::shared_ptr<Logger> getLogger() const { return _logger;}
    LogLevel::Level getLevel() const { return _level;}

    std::stringstream& getSS() { return _ss;}

    void format(const char* fmt, ...);
    void format(const char* fmt, va_list al);

private:
    const char* _file = nullptr;
    int32_t _line = 0;
    uint32_t _elapse = 0;
    uint32_t _threadId = 0;
    uint32_t _coroutineId = 0;
    uint64_t _timestamp;

    std::string _content;

    std::stringstream _ss;

    std::shared_ptr<Logger> _logger;
    LogLevel::Level _level;
};

class LogEventWrap {
public:
    LogEventWrap(LogEvent::ptr e);
    ~LogEventWrap();
    LogEvent::ptr getEvent() const { return _event;}
    std::stringstream& getSS();
private:
    LogEvent::ptr _event;
};

class Formatter {
public:
    typedef std::shared_ptr<Formatter> ptr;
    Formatter(const std::string& pattern);

    void init();
    std::string format(LogLevel::Level level, LogEvent::ptr event);

public:
    class FormatItem {
    public:
        typedef std::shared_ptr<FormatItem> ptr;
        virtual ~FormatItem() {}
        virtual void format(std::ostream& os, LogLevel::Level level, LogEvent::ptr event) = 0;
    };

private:
    std::string _pattern;
    std::vector<FormatItem::ptr> _items;
};


class Appender {
public:
    typedef std::shared_ptr<Appender> ptr;

    virtual ~Appender() {};
    virtual void log(LogLevel::Level level, LogEvent::ptr event) = 0;

    void setFormatter(Formatter::ptr formatter) { _formatter = formatter; }
    Formatter::ptr getFormatter() const { return _formatter; }

protected:
    LogLevel::Level _level;
    Formatter::ptr _formatter;
};

class StdLogAppender : public Appender {
public:
    typedef std::shared_ptr<StdLogAppender> ptr;
    virtual void log(LogLevel::Level level, LogEvent::ptr event) override;
};

class FileLogAppender : public Appender {
public:
    typedef std::shared_ptr<FileLogAppender> ptr;

    FileLogAppender(const std::string& filename);
    virtual void log(LogLevel::Level level, LogEvent::ptr event) override;
    bool reopen();

private:
    std::string _filename;
    std::ofstream _file;
};


class Logger : public std::enable_shared_from_this<Logger> {
public:
    typedef std::shared_ptr<Logger> ptr;

    Logger(const std::string &name = "root");
    
    void log(LogLevel::Level level, LogEvent::ptr event);

    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addAppender(Appender::ptr appender);
    void delAppender(Appender::ptr appender);
    LogLevel::Level getLevel() const { return _level; }
    void setLevel(LogLevel::Level level) { _level = level; }

    const std::string& getName() const { return _name;}

private:
    std::string _name;
    LogLevel::Level _level;
    std::list<Appender::ptr> _appenders;
    Formatter::ptr _formatter;
};
#endif // __LOGGER_H__