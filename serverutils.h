#ifndef SERVERUTILS_H
#define SERVERUTILS_H
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QStandardPaths>
#include <QDir>
#include <QSqlQuery>

class serverUtils
{
public:
    serverUtils();
    setupDatabase();
    createTable();
    insertData();
    getData();
};

#endif // SERVERUTILS_H
