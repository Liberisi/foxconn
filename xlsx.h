#ifndef XLSX_H
#define XLSX_H

#include<QtXlsx>
#include<QDateTime>

class xlsx
{
public:
    xlsx();

    String xlsx(QDateTime &Datetime);
};

#endif // XLSX_H
