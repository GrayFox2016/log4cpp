#include "logger.h"

Logger::Logger(const std::string &name)
    : _name(name),
    _level(LogLevel::DEBUG) {
    _formatter.reset(new Formatter("%d{%Y-%m-%d %H:%M:%S}%T%t%T%F%T[%p]%T[%c]%T%f:%l%T%m%n"));

}

void Logger::addAppender(Appender::ptr appender) {
    if(!appender->getFormatter()) {
        appender->setFormatter(_formatter);
    }
    _appenders.push_back(appender);

}
void Logger::delAppender(Appender::ptr appender) {
    for (auto it = _appenders.begin(); it != _appenders.end(); ++it) {
        if (*it == appender) {
            _appenders.erase(it);
            break;
        }
    }
}

void Logger::log(LogLevel::Level level, LogEvent::ptr event) {
    if (level >= _level) {
        for (auto &appender : _appenders) {
            appender->log(level, event);
        }
    }
}

void Logger::debug(LogEvent::ptr event) {
    log(LogLevel::DEBUG, event);
}
void Logger::info(LogEvent::ptr event) {
    log(LogLevel::INFO, event);   
}
void Logger::warn(LogEvent::ptr event) {
    log(LogLevel::WARN, event);   
}
void Logger::error(LogEvent::ptr event) {
    log(LogLevel::ERROR, event);   
}
void Logger::fatal(LogEvent::ptr event){
    log(LogLevel::FATAL, event);   
}   