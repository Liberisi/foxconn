#include "class_configparam.h"
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QVariantList>
#include <QSqlError>

Class_ConfigParam * Class_ConfigParam::class_ConfigParam = NULL;
QString Class_ConfigParam::dateName = "";
int Class_ConfigParam::circle1 = 20, Class_ConfigParam::circle2 =60, Class_ConfigParam::circle3 = 30;

Class_ConfigParam * Class_ConfigParam::GetInstance(QString path_Database)
{
    if  (class_ConfigParam == NULL)
    {
        class_ConfigParam = new Class_ConfigParam(path_Database);
    }
    return class_ConfigParam;
}

Class_ConfigParam::Class_ConfigParam(QString path_Database, QObject *parent) : QObject(parent)
{

    QFileInfo fileInfo(path_Database);
    if(fileInfo.exists()==false)
    {
        QDir dir;
        dir.mkpath(fileInfo.absolutePath());
        QFile file(path_Database);
        if(file.open(QIODevice::WriteOnly|QIODevice::Text)==false)
        {
            qDebug()<<"File open failed !";
        }
        file.close();

        InitDatabase(path_Database);

        CreateTable();
    }
    else
    {
        InitDatabase(path_Database);
        SeleteData("");
    }

}

QString Class_ConfigParam::GetName()
{
    return dateName;
}
int Class_ConfigParam::GetCircle1()
{
    return circle1;
}
int Class_ConfigParam::GetCircle2()
{
    return circle2;
}
int Class_ConfigParam::GetCircle3()
{
    return circle3;
}


void Class_ConfigParam::InitDataFile(QString path)
{
    QFileInfo fileInfo(path);
    if(fileInfo.exists()==false)
    {
        QDir dir;
        dir.mkpath(fileInfo.absolutePath());
        QFile file(path);
        if(file.open(QIODevice::WriteOnly|QIODevice::Text)== false)
        {
            qDebug()<<"File open failed !";
        }
        file.close();
    }
}

void Class_ConfigParam::InitDatabase(QString path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
}

void Class_ConfigParam::CreateTable()
{
    if(db.isOpen()==false)
    {
        if(db.open()==false)
        {
            qDebug()<<"Open Database is faild !";
            return;
        }
    }
    QSqlQuery query = QSqlQuery(db);
    QString str_Sql = QString("create table Table_Config (id int primary key, name varchar(255), circle1 int, circle2 int, circle3 int)");
    bool flag_Result = query.exec(str_Sql);
    if(flag_Result == false)
    {
        qDebug()<<"Create Table is faild !"
             <<query.lastError();
    }
    db.close();
}

void Class_ConfigParam::InsertData(QString name, int circle1, int circle2, int circle3)
{
    if(db.isOpen()==false)
    {
        if(db.open()==false)
        {
            qDebug()<<"Open Database is faild !";
            return;
        }
    }
    QString select_max_sql = "select max(id) from Table_Config";
    QSqlQuery query = QSqlQuery(db);
    bool flag_Result=query.exec(select_max_sql);
    if(flag_Result == false)
    {
        qDebug()<<"select_max_sql is faild !"
             <<query.lastError();
        db.close();
        return;
    }
    int id = 0;
    while   (query.next())
    {
        id = query.value("id").toInt()+1;
        qDebug()<<id;
    }
    QString str_Sql = QString("insert into Table_Config (id, name , circle1, circle2, circle3) values(:id, :name, :circle1, :circle2, :circle3);");

    QVariantList list_Id, list_Name, list_Circle1, list_Circle2, list_Circle3;
    list_Id.append(id);
    list_Name.append(name);
    list_Circle1.append(circle1);
    list_Circle2.append(circle2);
    list_Circle3.append(circle3);

    query.clear();
    query.prepare(str_Sql);

    query.bindValue(":id", list_Id);
    query.bindValue(":name", list_Name);
    query.bindValue(":circle1", list_Circle1);
    query.bindValue(":circle2", list_Circle2);
    query.bindValue(":circle3", list_Circle3);

    flag_Result = query.execBatch();
    if(flag_Result == false)
    {
        qDebug()<<"insert data is faild !"
             <<query.lastError();
        db.close();
        return;
    }

    query.exec("select * from Table_Config");
    while(query.next())
    {
        qDebug()<<query.value("id").toInt()
               <<query.value("name").toString()
              <<query.value("circle1").toInt()
             <<query.value("circle2").toInt()
            <<query.value("circle3").toInt();
    }
    db.close();
}

void Class_ConfigParam::UpdateData(QString name, int circle1, int circle2, int circle3)
{
    if(db.isOpen()==false)
    {
        if(db.open()==false)
        {
            qDebug()<<"Open Database is faild !";
            return;
        }
    }
    QString str_Sql = "update Table_Config set circle1=:circle1, circle2=:circle2, circle3=:circle3 where name=:name";

    QSqlQuery query = QSqlQuery(db);

    QVariantList list_Name, list_Circle1, list_Circle2, list_Circle3;

    list_Name.append(name);
    list_Circle1.append(circle1);
    list_Circle2.append(circle2);
    list_Circle3.append(circle3);

    query.prepare(str_Sql);

    query.bindValue(":name", list_Name);
    query.bindValue(":circle1", list_Circle1);
    query.bindValue(":circle2", list_Circle2);
    query.bindValue(":circle3", list_Circle3);

    bool flag_Result = query.execBatch();
    if(flag_Result == false)
    {
        qDebug()<<"update data is faild !"
             <<query.lastError();
        db.close();
        return;
    }

    query.exec("select * from Table_Config");
    while(query.next())
    {
        qDebug()<<query.value("id").toInt()
               <<query.value("name").toString()
              <<query.value("circle1").toInt()
             <<query.value("circle2").toInt()
            <<query.value("circle3").toInt();
    }
    db.close();
}

void Class_ConfigParam::SeleteData(QString name)
{
    if(db.isOpen()==false)
    {
        if(db.open()==false)
        {
            qDebug()<<"Open Database is faild !";
            return;
        }
    }
    QString str_Sql = "select * from Table_Config where name=:name";

    QSqlQuery query = QSqlQuery(db);

    QVariantList list_Name;

    list_Name.append(name);


    query.prepare(str_Sql);

    query.bindValue(":name", list_Name);

   bool flag_Result = query.execBatch();
    if(flag_Result == false)
    {
        qDebug()<<"select data is faild !"
             <<query.lastError();
        db.close();
        return;
    }

    if(query.next())
    {
        qDebug()<<query.value("id").toInt()
               <<query.value("name").toString()
              <<query.value("circle1").toInt()
             <<query.value("circle2").toInt()
            <<query.value("circle3").toInt();

        this->dateName  = query.value("name").toString();
        circle1= query.value("circle1").toInt();
        circle2=query.value("circle2").toInt();
        circle3=query.value("circle3").toInt();
    }
    else
    {
        InsertData(name, this->circle1, this->circle2, this->circle3);
        SeleteData(name);
        return;
    }

    query.clear();
    query.exec("select * from Table_Config");
    while(query.next())
    {
        qDebug()<<query.value("id").toInt()
               <<query.value("name").toString()
              <<query.value("circle1").toInt()
             <<query.value("circle2").toInt()
            <<query.value("circle3").toInt();
    }
    db.close();
}
