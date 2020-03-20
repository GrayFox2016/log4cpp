#ifndef __LOGEVENT_H__
#define __LOGEVENT_H__

#include <string>
#include <memory>
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

private:
    const char* _file = nullptr;
    int32_t _line = 0;
    uint32_t _elapse = 0;
    uint32_t _threadId = 0;
    uint32_t _coroutineId = 0;
    uint64_t _timestamp;

    std::string _content;
};

#endif // __LOGEVENT_H__