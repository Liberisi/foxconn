#ifndef DATETIMEFILESYSTEM_H
#define DATETIMEFILESYSTEM_H

#include <string>
#include <QDateTime>

using namespace std;

class DateTimeFileSystem
{
public:
    DateTimeFileSystem(string root_path);

    /**
     * 创建并返回目录路径
     */
    string directory_path(QDateTime& datetime);
    string directory_path(QDate& date);
    string directory_path_ng(QDateTime& datetime);
    string directory_path_ng(QDate& date);
    /**
     * 返回文件路径，并创建目录
     */
    string file_path(QDateTime& datetime, string filename);
    string file_path_ng(QDateTime& datetime, string filename);

private:
    string root_path_;
};

#endif // DATETIMEFILESYSTEM_H
