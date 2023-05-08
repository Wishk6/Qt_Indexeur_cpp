#ifndef DATABASEUTILS_H
#define DATABASEUTILS_H

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QStandardPaths>
#include <QDir>
#include <QSqlQuery>
#include <fileInfoStruct.h>
#include <QQueue>

class DatabaseUtils : public QObject
{

public:
    DatabaseUtils();
    int setupDatabase();
    int createTable();
    void insertDataFromQueue(QQueue<FileInfo>* _queue);
    int getData();
    void setQueue(QQueue<FileInfo> *queue);
    int countItems();
    QVector<FileInfo> getDataWithParams(QString formattedInput,QString fileName);
private:
    QSqlDatabase  _db;
};

#endif // DATABASEUTILS_H
