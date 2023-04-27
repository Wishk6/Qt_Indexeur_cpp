#include "serverutils.h"

struct FileInfo {
   QString name;
   QString path;
   QDateTime created_at;
   QDateTime updated_at;
   qint64 size;
   QString extension;
};

serverUtils::serverUtils()
{

}

serverUtils::setupDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    if (db.lastError().isValid()) {
        qCritical() << "add Database" << db.lastError().text();
        return -1;
    }

    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    QDir dir(appDataLocation);
    if (!dir.exists()) {
        dir.mkdir(appDataLocation);
        qDebug() << "mkdir" << appDataLocation;
    }
    // setup db file + open
    QString dbPath = appDataLocation+"_db.db";
    qDebug() << "dbPath" << dbPath;
    db.setDatabaseName(dbPath);

    if(!db.open()) {
        qCritical() << "unable open db" << db.lastError().text() << dbPath;
        return -1;
    }
}

serverUtils::createTable()
{
    QString createFileTable = "CREATE TABLE IF NOT EXISTS files ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "fileName VARCHAR(255),"
                              "filePath VARCHAR(255),"
                              " creationDate VARCHAR(20),"
                              " modificationDate VARCHAR(20),"
                              " size VARCHAR(20),"
                              " extension VARCHAR(10))";

    QSqlQuery query;
    query.exec(createFileTable);

    if(query.lastError().isValid()) {
        qWarning() << "CREATE TABLE" << query.lastError().text();
        return -1;
    }
    // return data TODO

}

serverUtils::insertData(FileInfo fileInformation)
{

    QSqlDatabase::database().transaction();

    // Insert file information into the database
    QSqlQuery query(db);
    query.prepare("INSERT INTO file_info (name, path) VALUES (:name, :path)");
    query.bindValue(":name", fileInformation.name);
    query.bindValue(":path", fileInformation.path);
    if (!query.exec()) {
        qDebug() << "Cannot insert data:" << query.lastError().text();

        // Rollback the transaction on error
        QSqlDatabase::database().rollback();
        return;
    }

    if (query.lastError().isValid()) {
        qWarning() << "Insert in  TABLE" << query.lastError().text();
        return -1;
    }

}

serverUtils::getData()
{
    QSqlQuery query;
    QString sqlSelect = "SELECT * FROM files";
    query.exec(sqlSelect);


    if (query.lastError().isValid()) {
        qWarning() << "SELECT" << query.lastError().text();
        return -1;
    }

    while(query.next()) {
        uint id = query.value("id").toUInt();
        QString fileName = query.value("fileName").toString();
        QString filePath = query.value("filePath").toString();
        QString creationDate = query.value("creationDate").toString();
        QString modificationDate = query.value("modificationDate").toString();
        QString size = query.value("size").toString();
        QString extension = query.value("extension").toString();
        qDebug()  << id << filePath << fileName << extension;
    }

}
