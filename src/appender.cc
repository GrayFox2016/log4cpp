#include "logger.h"

void StdLogAppender::log(LogLevel::Level level, LogEvent::ptr event) {
    if (level >= _level) {
        std::cout << _formatter->format(level, event);
    }
}

FileLogAppender::FileLogAppender(const std::string& filename)
    : _filename(filename) {
}

void FileLogAppender::log(LogLevel::Level level, LogEvent::ptr event) {
    if (level >= _level) {
        _file << _formatter->format(level, event);
    }
}

bool FileLogAppender::reopen() {
    if (_file)
        _file.close();

    _file.open(_filename);

    return !!_file;
}