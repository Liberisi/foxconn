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
     * datetime 可以理解成 date 和 time 的组合
     * 如果 time 在 h1:m1 之前，返回 date 前一天的夜班目录
     * 如果 time 在 h1:m1 之后，h2:m2 之间，返回 date 的白班目录
     * 如果 time 在 h2:m2 之后，返回 date 的夜班目录
     */
    string directory_path(QDateTime& datetime, string ng, int h1 = 8, int m1 = 0, int h2 = 18, int m2 = 0);
    string directory_path(QDate& date, int group, bool ng);
    //string directory_path_ng(QDateTime& datetime, int h1 = 8, int m1 = 0, int h2 = 18, int m2 = 0);
    //string directory_path_ng(QDate& date);
  //  string directory_
    /**
     * 返回文件路径，并创建目录
     */
    string file_path(QDateTime& datetime, string filename);
    string file_path_ng(QDateTime& datetime, string filename);

private:
    string root_path_;
};

#endif // DATETIMEFILESYSTEM_H
