#include "datetime_filesystem.h"
#include <QDir>
#include <QDateTime>
#include <QDate>

DateTimeFileSystem::DateTimeFileSystem(string root_path):root_path_(root_path)
{

}

string DateTimeFileSystem::directory_path(QDate& date, int group, bool ng)
{
    int year = date.year();
    int month = date.month();
    int day = date.day();
    QChar sep = QDir::separator();
    // 2019
    QString year_str = QString().sprintf("%04d", year);
    // 201909
    QString year_month_str = QString().sprintf("%04d%02d", year, month);
    // 20190931_2
    QString year_month_day_str;

        if (ng > 0)
        {
            year_month_day_str = QString().sprintf("%04d%02d%02d_%d_ng", year, month, day, group);
        }
        else
        {
            year_month_day_str = QString().sprintf("%04d%02d%02d_%d", year, month, day, group);
        }


    QString related_dir_path = year_str + sep + year_month_str + sep + year_month_day_str + sep;
    QDir dir(root_path_.c_str());
    dir.mkpath(related_dir_path);
    QString dir_path = QString(root_path_.c_str()) + sep + related_dir_path;
    return dir_path.toStdString();
}

/**
 * 创建并返回目录路径
 */
string DateTimeFileSystem::directory_path(QDateTime& datetime, string ng, int h1, int m1, int h2, int m2)
{
    QDate date = datetime.date();
    QTime time = datetime.time();
    //int year, month, day;
    int hour = time.hour();
    int minute = time.minute();
    bool last_day = false;
    if (hour < h1)
    {
        last_day = true;
    }
    else if (hour == h1)
    {
        if (minute < m1)
        {
            last_day = true;
        }
    }

    bool first_group = false;
    if (last_day)
    {
        date = date.addDays(-1);
        first_group = false;
    }
    else
    {
        //bool first_group = false;
        if (hour < h2)
        {
            first_group = true;
        }
        else if (hour == h2)
        {
            if (minute < m2)
            {
                first_group = true;
            }
        }
    }

    int year = date.year();
    int month = date.month();
    int day = date.day();
    QChar sep = QDir::separator();
    // 2019
    QString year_str = QString().sprintf("%04d", year);
    // 201909
    QString year_month_str = QString().sprintf("%04d%02d", year, month);
    // 20190931_2
    QString year_month_day_str;
    if (first_group)
    {
        if (ng.length() > 0)
        {
            year_month_day_str = QString().sprintf("%04d%02d%02d_1_%s", year, month, day, ng.c_str());
        }
        else
        {
            year_month_day_str = QString().sprintf("%04d%02d%02d_1", year, month, day);
        }

    }
    else
    {
        if (ng.length() > 0)
        {
            year_month_day_str = QString().sprintf("%04d%02d%02d_2_%s", year, month, day, ng.c_str());
        }
        else
        {
            year_month_day_str = QString().sprintf("%04d%02d%02d_2", year, month, day);
        }
    }
    QString related_dir_path = year_str + sep + year_month_str + sep + year_month_day_str + sep;
    QDir dir(root_path_.c_str());
    dir.mkpath(related_dir_path);
    QString dir_path = QString(root_path_.c_str()) + sep + related_dir_path;
    return dir_path.toStdString();
}

//string DateTimeFileSystem::directory_path(QDateTime& datetime)
//{
//    return directory_path(datetime.date());
//}

//string DateTimeFileSystem::directory_path_ng(QDate& date)
//{
//    int year = date.year();
//    int month = date.month();
//    int day = date.day();
//    QChar sep = QDir::separator();
//    // 2019
//    QString year_str = QString().sprintf("%04d", year);
//    // 201909
//    QString year_month_str = QString().sprintf("%04d%02d", year, month);
//    // 20190931
//    QString year_month_day_str = QString().sprintf("%04d%02d%02d_ng", year, month, day);
//    QString related_dir_path = year_str + sep + year_month_str + sep + year_month_day_str + sep;
//    QDir dir(root_path_.c_str());
//    dir.mkpath(related_dir_path);
//    QString dir_path = QString(root_path_.c_str()) + sep + related_dir_path;
//    return dir_path.toStdString();
//}

//string DateTimeFileSystem::directory_path_ng(QDateTime& datetime)
//{
//    return directory_path_ng(datetime.date());
//}

/**
 * 返回文件路径但不创建
 */
string DateTimeFileSystem::file_path(QDateTime& datetime, string filename)
{
    string dir_path = directory_path(datetime, "");
    QString file_path = QString(dir_path.c_str()) + QDir::separator() + QString(filename.c_str());
    return file_path.toStdString();
}

string DateTimeFileSystem::file_path_ng(QDateTime& datetime, string filename)
{
    string dir_path = directory_path(datetime, "ng");
    QString file_path = QString(dir_path.c_str()) + QDir::separator() + QString(filename.c_str());
    return file_path.toStdString();
}
