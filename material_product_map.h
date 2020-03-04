#ifndef MATERIALPRODUCTMAP_H
#define MATERIALPRODUCTMAP_H

#include <string>
#include <QSqlDatabase>

using namespace std;

class MaterialProductMap
{
public:
    MaterialProductMap();

    void open(const string db_path);
    void insert(string material, string product);
    void remove(string material);
    bool exist(string material, string& product);
    void update(string material, string product);

private:
     QSqlDatabase db_;
};

#endif // MATERIALPRODUCTMAP_H
