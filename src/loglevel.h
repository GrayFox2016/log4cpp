#ifndef __LOGLEVEL_H__
#define __LOGLEVEL_H__

#include <string>

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
    
    static LogLevel::Level FromString(const std::string& str);
};

#endif // __LOGLEVEL_H__