#include "datetime_filesystem.h"
#include <QDir>
#include <QDateTime>
#include <QDate>

DateTimeFileSystem::DateTimeFileSystem(string root_path):root_path_(root_path)
{

}

/**
 * 创建并返回目录路径
 */
string DateTimeFileSystem::directory_path(QDate& date)
{
    int year = date.year();
    int month = date.month();
    int day = date.day();
    QChar sep = QDir::separator();
    // 2019
    QString year_str = QString().sprintf("%04d", year);
    // 201909
    QString year_month_str = QString().sprintf("%04d%02d", year, month);
    // 20190931
    QString year_month_day_str = QString().sprintf("%04d%02d%02d", year, month, day);
    QString related_dir_path = year_str + sep + year_month_str + sep + year_month_day_str + sep;
    QDir dir(root_path_.c_str());
    dir.mkpath(related_dir_path);
    QString dir_path = QString(root_path_.c_str()) + sep + related_dir_path;
    return dir_path.toStdString();
}
string DateTimeFileSystem::directory_path(QDateTime& datetime)
{
    return directory_path(datetime.date());
}

string DateTimeFileSystem::directory_path_ng(QDate& date)
{
    int year = date.year();
    int month = date.month();
    int day = date.day();
    QChar sep = QDir::separator();
    // 2019
    QString year_str = QString().sprintf("%04d", year);
    // 201909
    QString year_month_str = QString().sprintf("%04d%02d", year, month);
    // 20190931
    QString year_month_day_str = QString().sprintf("%04d%02d%02d_ng", year, month, day);
    QString related_dir_path = year_str + sep + year_month_str + sep + year_month_day_str + sep;
    QDir dir(root_path_.c_str());
    dir.mkpath(related_dir_path);
    QString dir_path = QString(root_path_.c_str()) + sep + related_dir_path;
    return dir_path.toStdString();
}

string DateTimeFileSystem::directory_path_ng(QDateTime& datetime)
{
    return directory_path_ng(datetime.date());
}

/**
 * 返回文件路径但不创建
 */
string DateTimeFileSystem::file_path(QDateTime& datetime, string filename)
{
    string dir_path = directory_path(datetime);
    QString file_path = QString(dir_path.c_str()) + QDir::separator() + QString(filename.c_str());
    return file_path.toStdString();
}

string DateTimeFileSystem::file_path_ng(QDateTime& datetime, string filename)
{
    string dir_path = directory_path_ng(datetime);
    QString file_path = QString(dir_path.c_str()) + QDir::separator() + QString(filename.c_str());
    return file_path.toStdString();
}
