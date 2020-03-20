#include "appender.h"

void StdLogAppender::log(LogLevel::Level level, LogEvent::ptr event) {
    if (level >= _level) {
        std::cout << _formatter->format(event);
    }
}

FileLogAppender::FileLogAppender(const std::string& filename)
    : _filename(filename) {
}

void FileLogAppender::log(LogLevel::Level level, LogEvent::ptr event) {
    if (level >= _level) {
        _file << _formatter->format(event);
    }
}

bool FileLogAppender::reopen() {
    if (_file)
        _file.close();

    _file.open(_filename);

    return !!_file;
}