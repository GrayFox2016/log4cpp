#ifndef __FORMATTER_H__
#define __FORMATTER_H__

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <ostream>
#include <map>
#include "logevent.h"

class Formatter {
public:
    typedef std::shared_ptr<Formatter> ptr;
    Formatter(const std::string& pattern);

    void init();
    std::string format(LogEvent::ptr event);

public:
    class FormatItem {
    public:
        typedef std::shared_ptr<FormatItem> ptr;
        virtual ~FormatItem() {}
        virtual void format(std::ostream& os, LogEvent::ptr event) = 0;
    };

private:
    std::string _pattern;
    std::vector<FormatItem::ptr> _items;
};

#endif // __FORMATTER_H__