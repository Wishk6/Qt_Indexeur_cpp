#include "databaseutils.h"


DatabaseUtils::DatabaseUtils() :
    _db(QSqlDatabase())
{
}

int DatabaseUtils::setupDatabase()
{
    _db = QSqlDatabase::addDatabase("QSQLITE");
    if (_db.lastError().isValid()) {
        qCritical() << "add Database" << _db.lastError();
        return -1;
    }

    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    QDir dir(appDataLocation);
    if (!dir.exists()) {
        dir.mkdir(appDataLocation);
        qDebug() << "mkdir" << appDataLocation;
    }
    // setup db file + open
    QString dbPath = appDataLocation+"files_db.db";
    qDebug() << "dbPath" << dbPath;
    _db.setDatabaseName(dbPath);

    if(!_db.open()) {
        qCritical() << "unable open db" << _db.lastError().text() << dbPath;
        return -1;
    }

    return 0; // retourner 0 si tout s'est bien passé
}

int DatabaseUtils::createTable()
{
    QString createFileTable = "CREATE TABLE IF NOT EXISTS filesInfo ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "name VARCHAR(255),"
                              "path VARCHAR(255),"
                              "created_at VARCHAR(120),"
                              "updated_at VARCHAR(120),"
                              "size BIGINT,"
                              "extension VARCHAR(10))";

    QSqlQuery query(_db); // utilisez la variable db pour la requête
    query.exec(createFileTable);

    if(query.lastError().isValid()) {
        qWarning() << "CREATE TABLE" << query.lastError().text();
        return -1;
    }
    return 0; // retourner 0 si tout s'est bien passé
}

void DatabaseUtils::setQueue(QQueue<FileInfo>* queue) {
    queue = queue;
}

void DatabaseUtils::insertDataFromQueue(QQueue<FileInfo>* queue)
{
    if (queue->isEmpty()) {
        return;
    }

    _db.transaction();

    QSqlQuery query(_db);

    // préparer la requête SQL pour insérer toutes les données de la queue en une seule fois
    QString queryStr = "INSERT INTO filesInfo (name, path, created_at, updated_at, size, extension) VALUES ";
    QStringList values;

    while (!queue->isEmpty()) {
        FileInfo fileInfo = queue->dequeue();
        // ajouter les valeurs de chaque fichier à la liste des valeurs
        values.append(QString("('%1', '%2', '%3', '%4', %5, '%6')")
                      .arg(fileInfo.name)
                      .arg(fileInfo.path)
                      .arg(fileInfo.created_at.toString())
                      .arg(fileInfo.updated_at.toString())
                      .arg(fileInfo.size)
                      .arg(fileInfo.extension));
    }


    query.exec(queryStr + values.join(","));

    if (query.lastError().isValid()) {
        qWarning() << "Insert in TABLE" << query.lastError().text();
        _db.rollback();
    } else {
        _db.commit();
    }
}

int DatabaseUtils::getData()
{
    QSqlQuery query;
    QString sqlSelect = "SELECT * FROM filesInfo";
    query.exec(sqlSelect);


    if (query.lastError().isValid()) {
        qWarning() << "SELECT" << query.lastError().text();
        return -1;
    }

    while(query.next()) {
        uint id = query.value("id").toUInt();
        QString fileName = query.value("name").toString();
        QString filePath = query.value("path").toString();
        QString creationDate = query.value("created_at").toString();
        QString modificationDate = query.value("updated_at").toString();
        QString size = query.value("size").toString();
        QString extension = query.value("extension").toString();
        qDebug()  << id << filePath << fileName << extension;
    }
    return 0;
}

int DatabaseUtils::countItems() {
    int count = 0;

    QSqlQuery query(_db);
    if (query.exec("SELECT COUNT(*) FROM filesInfo")) {
        if (query.next()) {
            count = query.value(0).toInt();
        }
    } else {
        qDebug() << "Erreur lors de la requête COUNT : " << query.lastError().text();
    }
    return count;
}

QVector<FileInfo> DatabaseUtils::getDataWithParams(QString fileName, QString queryInput) {
    QVector<FileInfo> result;
    if(_db.open()) {
        QSqlQuery query(_db);
        qDebug() << queryInput;
        qDebug() << fileName;
        query.prepare(queryInput);
        query.bindValue(":file", fileName);
        query.exec();
        if(!query.exec()) {
            qDebug() << query.lastError().text();
            return result;
        }

        while(query.next()) {
            FileInfo fileInfo;
            fileInfo.name = query.value("filename").toString();
            fileInfo.path = query.value("path").toString();
            fileInfo.created_at = QDateTime::fromString(query.value("creation_date").toString(), "yyyy-MM-ddThh:mm:ss");
            fileInfo.updated_at = QDateTime::fromString(query.value("last_modified").toString(), "yyyy-MM-ddThh:mm:ss");
            fileInfo.size = query.value("size").toLongLong();
            fileInfo.extension = query.value("ext").toString();
            result.append(fileInfo);
        }
    } else {
        qDebug() << "Error while opening database";
    }
    return result;
}

