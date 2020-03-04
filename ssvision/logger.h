#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <map>

using namespace std;

namespace ssvision {

/**
 * 日志类提供基本打开日志文件的方法和基本日志方法
 * 可以继承Logger，通过子类来实现更丰富的日志文件格式
 */
class Logger
{
public:
    typedef enum
    {
        kLogLevelInfo,
        kLogLevelWarning,
        kLogLevelError,
        kLogLevelCount,
    } Level;

protected:
    Logger();
public:
    virtual ~Logger(){}

public:
    virtual bool isopen() = NULL;
    virtual bool open() = NULL;
    virtual void close() = NULL;

    /**
     * 20190817 10:00:59 info[*warn][***error] user    operation      old_value    ->    new_value
     **/
    virtual void log(Level level, const string user, const string operation) = NULL;
    virtual void log(Level level, const string user, const string operation, const string param) = NULL;
    virtual void log(Level level, const string user, const string operation, const int old_value, const int new_value) = NULL;
    virtual void log(Level level, const string user, const string operation, const float old_value, const float new_value) = NULL;
    virtual void log(Level level, const string user, const string operation, const string old_value, const string new_value) = NULL;
    virtual void log(Level level, const string message) = NULL;
	virtual void logline(const string message) = NULL;
};

}

#endif // LOGGER_H
