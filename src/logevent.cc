#include "logevent.h"

LogEvent::LogEvent(// std::shared_ptr<Logger> logger, LogLevel::Level level
            const char* file, int32_t line, uint32_t elapse
            , uint32_t threadId, uint32_t coroutineId, uint64_t timestamp, const std::string& content)
    :_file(file),
    _line(line),
    _elapse(elapse),
    _threadId(threadId),
    _coroutineId(coroutineId),
    _timestamp(timestamp),
    _content(content)
    // _logger(logger),
    // _level(level) ,
    {
}

// LogEventWrap::LogEventWrap(LogEvent::ptr e)
//     :_event(e) {
// }

// LogEventWrap::~LogEventWrap() {
//     _event->getLogger()->log(_event->getLevel(), _event);
// }

// void LogEvent::format(const char* fmt, ...) {
//     va_list al;
//     va_start(al, fmt);
//     format(fmt, al);
//     va_end(al);
// }

// void LogEvent::format(const char* fmt, va_list al) {
//     char* buf = nullptr;
//     int len = vasprintf(&buf, fmt, al);
//     if(len != -1) {
//         m_ss << std::string(buf, len);
//         free(buf);
//     }
// }

// std::stringstream& LogEventWrap::getSS() {
//     return m_event->getSS();
// }
