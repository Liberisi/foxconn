#include "datefilelogger.h"
#include <QDir>

namespace ssvision {

DateFileLogger::DateFileLogger(string root_dir_path, string file_name):root_dir_path_(root_dir_path), file_name_(file_name)
{
    year_ = 0;
    month_ = 0;
    day_ = 0;
}

DateFileLogger::~DateFileLogger()
{
    close();
}

string DateFileLogger::related_dir_path()
{
    QChar sep = QDir::separator();
    // 2019
    QString year_str = QString().sprintf("%04d", year_);
    // 201909
    QString year_month_str = QString().sprintf("%04d%02d", year_, month_);
    // 20190931
    QString year_month_day_str = QString().sprintf("%04d%02d%02d", year_, month_, day_);
    QString dir_path = year_str + sep + year_month_str + sep + year_month_day_str + sep;
    return dir_path.toStdString();
}

string DateFileLogger::file_path()
{
    QChar sep = QDir::separator();
    QString root_path = QString(root_dir_path_.c_str());
    QString related_path = QString(related_dir_path().c_str());
    QString file_name = QString(file_name_.c_str());
    QString filepath = root_path + sep + related_path + sep + file_name;
    return filepath.toStdString();
}

bool DateFileLogger::isopen()
{
    return  file_stream_.is_open();
}

bool DateFileLogger::open()
{
    QDate date = QDate::currentDate();
    int year = date.year();
    int month = date.month();
    int day = date.day();
    return openfile(year, month, day);
}

bool DateFileLogger::openfile(int year, int month, int day)
{
    if (year == year_ && month == month_ && day == day_)
    {
        if (file_stream_.is_open())
            return true;
    }
    else
    {
        if (file_stream_.is_open())
            file_stream_.close();
        // 更新日期
        year_ = year;
        month_ = month;
        day_ = day;
        QDir dir(root_dir_path_.c_str());
        if (!dir.mkpath(related_dir_path().c_str()))
            return false;
    }
    string filepath = this->file_path();
    file_stream_.open(filepath, ofstream::out | ofstream::app);
    if ((file_stream_.rdstate() & ofstream::failbit ) != 0)
        return false;
    else
        return true;
}

void DateFileLogger::close()
{
    if (file_stream_.is_open())
        file_stream_.close();
}

void DateFileLogger::log(Level level, const string user, const string operation)
{
    string message = user + "\t\t" + operation;
    log(level, message);
}
void DateFileLogger::log(Level level, const string user, const string operation, const string param)
{
    string message = user + "\t\t" + operation + "\t\t" + param;
    log(level, message);
}
void DateFileLogger::log(Level level, const string user, const string operation, const int old_value, const int new_value)
{
    log(level, user, operation, to_string(old_value), to_string(new_value));
}
void DateFileLogger::log(Level level, const string user, const string operation, const float old_value, const float new_value)
{
    log(level, user, operation, to_string(old_value), to_string(new_value));
}
void DateFileLogger::log(Level level, const string user, const string operation, const string old_value, const string new_value)
{
    string message = user + "\t\t" + operation + "\t\t" + old_value + " -> " + new_value;
    log(level, message);
}
void DateFileLogger::log(Level level, const string message)
{
    string time_str = QTime::currentTime().toString("hh:mm:ss.zzz").toStdString();
    string level_str;
    switch (level) {
    case Logger::kLogLevelInfo:
        level_str = "info";
        break;
    case Logger::kLogLevelWarning:
        level_str = "* warning";
        break;
    case Logger::kLogLevelError:
        level_str = "*** error";
        break;
    default:
        level_str = "info";
        break;
    }
    logline(time_str + " " + level_str + "\t" + message);
}
void DateFileLogger::logline(string line)
{
    QDate date = QDate::currentDate();
    int year = date.year();
    int month = date.month();
    int day = date.day();
    if (year == year_ && month == month_ && day == day_ && file_stream_.is_open())
    {
        file_stream_ << line << endl;
    }
    else
    {
        if (openfile(year, month, day))
            file_stream_ << line << endl;
    }
}

}

