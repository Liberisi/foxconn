#ifndef CLASS_CONFIGPARAM_H
#define CLASS_CONFIGPARAM_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

class Class_ConfigParam : public QObject
{
    Q_OBJECT
public:
    static Class_ConfigParam * GetInstance(QString path_Database);

signals:


private:
    explicit Class_ConfigParam(QString path_Database, QObject *parent = 0);
    static Class_ConfigParam * class_ConfigParam;

    QSqlDatabase db;

    static QString dateName;
    static int circle1, circle2, circle3;

    void InitDataFile(QString path);
    void InitDatabase(QString path);
    void CreateTable();

public :

    static QString GetName();
    static int GetCircle1();
    static int GetCircle2();
    static int GetCircle3();

    void InsertData(QString name, int circle1, int circle2, int circle3);
    void UpdateData(QString name, int circle1, int circle2, int circle3);
    void SeleteData(QString name);

public slots:

};

#endif // CLASS_CONFIGPARAM_H
