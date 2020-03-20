## Log Module for CPP
* referenced by https://github.com/sylar-yin/sylar

## Test
* mkdir build && cd build
* cmake .. && make
* ./log4cpp

## Output
* 2020-03-20 20:46:44     17003   0       [DEBUG] [root]  /home/admin/code/log4cpp/src/test.cc:15 debug message
* 2020-03-20 20:46:44     17003   0       [ERROR] [root]  /home/admin/code/log4cpp/src/test.cc:16 hello logger stream
* 2020-03-20 20:46:44     17003   0       [DEBUG] [root]  /home/admin/code/log4cpp/src/test.cc:18 test macro fmt error aa

## Usage
```c
// define a global logger
static Logger::ptr g_logger(new Logger());

// test stream style logs
LOG_DEBUG(g_logger) << "debug message";
LOG_ERROR(g_logger) << "hello logger stream";

// test c-format style logs
FORMAT_LOG_DEBUG(g_logger, "test macro fmt error %s", "aa");
```

## Components
* Logger: main class
* Appender: class for log output, can be implemented in different ways, such as stdout, file, http, MQ, kafka etc.
* Formatter: class for string formatting. 
* LogEvent: wrap class for log trigger.
* LogLevel: log level definitions.