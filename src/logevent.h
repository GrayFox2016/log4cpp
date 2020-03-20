#ifndef __LOGEVENT_H__
#define __LOGEVENT_H__

#include <string>
#include <memory>
#include <sstream>
#include "loglevel.h"

class LogEvent {
public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent(//LogLevel::Level level, 
            const char* file, 
            int32_t line, 
            uint32_t elapse, 
            uint32_t threadId, 
            uint32_t coroutineId, 
            uint64_t timestamp,
            const std::string& content);

    const char* getFile() const { return _file;}
    int32_t getLine() const { return _line;}
    uint32_t getElapse() const { return _elapse;}
    uint32_t getThreadId() const { return _threadId;}
    uint32_t getCoroutineId() const { return _coroutineId;}
    uint64_t getTime() const { return _timestamp;}
    std::string getContent() const { return _ss.str();}
    //std::shared_ptr<Logger> getLogger() const { return _logger;}
    //LogLevel::Level getLevel() const { return _level;}

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

    //std::shared_ptr<Logger> _logger;
    //LogLevel::Level _level;
};

// class LogEventWrap {
// public:
//     LogEventWrap(LogEvent::ptr e);
//     ~LogEventWrap();
//     LogEvent::ptr getEvent() const { return _event;}
//     std::stringstream& getSS();
// private:
//     LogEvent::ptr _event;
// };

#endif // __LOGEVENT_H__