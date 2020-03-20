#include <afxwin.h>
#include<afx.h>
#include"UserIni.h"
#include <direct.h>
#include <iostream>
#include <strstream>
#include"fstream"
#include "io.h"
//#include<Windows.h>
#define  MY_PATH  4096

UserIni::UserIni()
{
    //UserIni::estab = false;
}
UserIni::~UserIni()
{

}
void UserIni::string_replaceAll(std::string &str, const std::string &src, const std::string &dst)
{
    std::string::size_type pos = 0;
    std::string::size_type srclen = src.size();
    std::string::size_type dstlen = dst.size();
    while ((pos = str.find(src, pos)) != std::string::npos)
    {
        str.replace(pos, srclen, dst);
        pos += dstlen;
    }
}

//写入用户信息
void UserIni::Write(string Grade, string Name, string Password,string* State)
{
    try
    {
        ///重复名字过滤

        ///保存用户信息
        CString grade, nsme, password, ini_path;
        grade = Grade.c_str();
        nsme = Name.c_str();
        password = Password.c_str();
        string_replaceAll(INI_Path, "\\", "//");
        ini_path = INI_Path.c_str();

        /*if (UserIni::estab)
        {*/
            int retnum;
            retnum = GetPrivateProfileInt(grade, nsme, 0, ini_path);//判断是否存在当前键
            if (retnum != 0)
            {
                *State = "NG_name";
                return;
            }
        //}

            if (WritePrivateProfileString(grade, nsme, password, ini_path))
        {
            *State = "OK";
        }
        else
        {
            *State = "NG";
        }

    }
    catch (exception ex)
    {
        *State = "用户创建异常";
    }
}

bool UserIni::Estab_ini(string name)
{
    try
    {
        char buffer[MAX_PATH];
        _getcwd(buffer, MAX_PATH);                                      //获取当前工程位置
        string path(buffer);
        path = path + "\\conconfiguration_file";
        if (_access(path.c_str(), 0) == -1)	                             //如果文件夹不存在
        {
            _mkdir(path.c_str());                                        //创建文件夹
        }
        string userini;
        userini = path + "\\" + name + ".ini";
        INI_Path = userini;
    /*	string_replaceAll(INI_Path, "\\", "//");
        INI_Path = INI_Path;*/
        return true;
    }
    catch (exception ex)
    {
            ::MessageBox(NULL, _T("配置文件建立异常"), _T("警告"), MB_OK);   //警告弹窗
            return false;
    }


}
void UserIni::Read()
{

}
