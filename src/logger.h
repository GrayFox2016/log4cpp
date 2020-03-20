#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <memory>
#include <list>
#include "loglevel.h"
#include "logevent.h"
#include "appender.h"

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