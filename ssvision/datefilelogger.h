#ifndef DATEFILELOGGER_H
#define DATEFILELOGGER_H

#include <logger.h>
#include <string>
#include <fstream>
#include <QDateTime>

namespace ssvision
{

class DateFileLogger : public Logger
{
public:
    DateFileLogger(string root_dir_path, string file_name);
    ~DateFileLogger();

    string root_dir_path() {return root_dir_path_;}
    string related_dir_path();
    string file_name() {return file_name_;}
    string file_path();
    bool isopen();
    bool open();
    void close();

    /**
     * 20190817 10:00:59 user    operation      old_value    ->    new_value
     **/
    virtual void log(Level level, const string user, const string operation);
    virtual void log(Level level, const string user, const string operation, const string param);
    virtual void log(Level level, const string user, const string operation, const int old_value, const int new_value);
    virtual void log(Level level, const string user, const string operation, const float old_value, const float new_value);
    virtual void log(Level level, const string user, const string operation, const string old_value, const string new_value);
    virtual void log(Level level, const string message);

	/**
	* 其他 log 方法都应该调用 logline 完成日期日志文件切换
	*/
	virtual void logline(const string line);

protected:

    virtual bool openfile(int year, int month, int day);

    int year_;
    int month_;
    int day_;

    string root_dir_path_;
    string file_name_;
    ofstream file_stream_;
};

}

#endif // DATEFILELOGGER_H
