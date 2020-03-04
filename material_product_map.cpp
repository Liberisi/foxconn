#include "material_product_map.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

MaterialProductMap::MaterialProductMap()
{

}

void MaterialProductMap::open(const string db_path)
{
    const QString driver("QSQLITE");
    if(QSqlDatabase::isDriverAvailable(driver))
    {
        db_ = QSqlDatabase::addDatabase(driver);
        db_.setDatabaseName(db_path.c_str());
        db_.open();
        QSqlQuery query("CREATE TABLE material (id TEXT PRIMARY KEY, product TEXT)");
        if(!query.isActive())
            qDebug() << "ERROR: " << query.lastError().text();
    }
}

void MaterialProductMap::insert(string material, string product)
{
    QSqlQuery query;
    string command = "INSERT INTO material (id, product) VALUES (";
    command += "\'"+material+"\',\'" + product + "\'" + ")";
    if(!query.exec(command.c_str()))
    {
        update(material, product);
    }
}

void MaterialProductMap::remove(string material)
{
    QSqlQuery query;
    string command = "DELETE FROM material WHERE id = ";
    command += "\'" + material + "\'";
    query.exec(command.c_str());
}

bool MaterialProductMap::exist(string material, string& product)
{
    QSqlQuery query;
    string command = "SELECT product FROM material WHERE id = ";
    command += "\'" + material + "\'";
    query.prepare(command.c_str());
    if(!query.exec())
    {
        return false;
    }
    else
    {
        bool find = false;
        while(query.next())
        {
            product = query.value(0).toString().toStdString();
            find = true;
        }
        return find;
    }
}

void MaterialProductMap::update(string material, string product)
{
    QSqlQuery query;
    string command = "UPDATE material set ";
    command += "product = '" + product + "' ";
    command += "WHERE id = ";
    command += "\'" + material + "\'";
    query.exec(command.c_str());
}
