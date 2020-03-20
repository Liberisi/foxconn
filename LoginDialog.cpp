#include "LoginDialog.h"
#include"qtextcodec.h"

#include <afxwin.h>

LoginDialog::LoginDialog(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    ////////////////////////////////------设置界面可以移动start-------////////////////////////////////////////////
    this->setWindowFlags(Qt::FramelessWindowHint);//无边框
    //this->setAttribute(Qt::WA_TranslucentBackground);//背景透明
    //m_areaMovable = geometry();
    //m_bPressed = false;
    ////////////////////////////////------设置界面可以移动end-------////////////////////////////////////////////
    userini.Estab_ini("User");
    ui.cob_grade->setCurrentIndex(0);

}

LoginDialog::~LoginDialog()
{

}

void LoginDialog::tol_exit_clicked()
{

}

void LoginDialog::Signin()
{
    if (ui.lin_password->text() == "")
    {
        ::MessageBox(NULL, _T("密码不能为空"), _T("警告"), MB_OK);   //警告弹窗
        return;
    }
    if (ui.cob_grade->currentText() != "管理员" && ui.cob_name->currentText() != name_line)
    {
        string grade, name, pass;
        QString mmm, nam;
        mmm = ui.cob_grade->currentText();  //获取控件信息
        nam = ui.cob_name->currentText();
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));     //设定编码信息
        QByteArray cdata, namedata;
        cdata = mmm.toLocal8Bit();
        namedata = nam.toLocal8Bit();
        grade = string(cdata);
        name = string(namedata);

        CString grade_in = grade.c_str();
        CString name_in = name.c_str();
        CString path_in = userini.INI_Path.c_str();
        TCHAR szKeyValue[MAX_PATH] = { 0 };
        GetPrivateProfileString(grade_in, name_in, NULL, szKeyValue, _MAX_PATH, path_in);

        QString bn = QString::fromStdWString(szKeyValue);
        pass = bn.toStdString();

        if (pass != ui.lin_password->text().toStdString())
        {
            ::MessageBox(NULL, _T("密码错误"), _T("警告"), MB_OK);   //警告弹窗
            return;
        }
        else
        {
            ::MessageBox(NULL, _T("登录成功"), _T("提示"), MB_OK);   //警告弹窗

            this->close();
        }
    }
    else
    {
        if (ui.lin_password->text() == pass_line)
        {
            ::MessageBox(NULL, _T("登录成功"), _T("提示"), MB_OK);   //警告弹窗
            return;
        }
        else
        {
            ::MessageBox(NULL, _T("登录成功"), _T("提示"), MB_OK);   //警告弹窗

            this->close();
        }
    }
}

void LoginDialog::cancel()
{
    ui.lin_password->clear();
}
void LoginDialog::Changed()
{
    string grade, name, pass;
    QString mmm;
    mmm = ui.cob_grade->currentText();                                  //获取控件信息
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));     //设定编码信息
    QByteArray cdata ,namedata;
    cdata = mmm.toLocal8Bit();
    grade = string(cdata);


    TCHAR szBuf[_MAX_PATH];
    memset(szBuf, 0, _MAX_PATH);
    TCHAR szWork[_MAX_PATH];
    memset(szWork, 0, _MAX_PATH);

    CString grade_in = grade.c_str();
    CString path_in = userini.INI_Path.c_str();
    INT nNum = 0;
    INT nCount = 0;
    INT nLen = 0;
    nNum = GetPrivateProfileSection(grade_in, szBuf, _MAX_PATH, path_in);

    nLen = _tcslen(szBuf);
    TCHAR* p = szBuf;
    ui.cob_name->clear();
    while (nLen < nNum)
    {
        _tcscpy(szWork, p);//此处的szWork为所需内容
        nLen = nLen + 1;
        p = &szBuf[nLen];
        nLen += _tcslen(p);
        //LPCTSTR pstrData = _tcschr(szWork,_T('='));
        QString name_find = QString::fromStdWString(szWork);
        string cut = name_find.toStdString().substr(0, name_find.toStdString().find_last_of("="));
        ui.cob_name->addItem(QString::fromStdString(cut));
    }
    if (grade == "管理员")
    {
        ui.cob_name->addItem("Alan");
    }
    //namedata = ui.cob_name->currentText().toLocal8Bit();;
    //name = string(namedata);
    //pass = ui.lin_password->text().toStdString();
}






