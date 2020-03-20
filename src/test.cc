#include <iostream>
#include "logger.h"

// define a global logger
static Logger::ptr g_logger(new Logger());
    
int main(int argc, char const *argv[])
{
    // add log appenders
    g_logger->addAppender(Appender::ptr(new StdLogAppender()));

    // test stream log
    LOG_DEBUG(g_logger) << "debug message";
    LOG_ERROR(g_logger) << "hello logger stream";

    // test format log
    FORMAT_LOG_DEBUG(g_logger, "test macro fmt error %s", "aa");

    return 0;
}

