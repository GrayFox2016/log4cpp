#ifndef __APPENDER_H__
#define __APPENDER_H__

#include <memory>
#include <string>
#include <fstream>
#include <iostream>
#include "loglevel.h"
#include "logevent.h"
#include "formatter.h"

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

#endif // __APPENDER_H__
