#ifndef INSERTIONTHREAD_H
#define INSERTIONTHREAD_H

#include <QThread>
#include <QSqlDatabase>
#include <QQueue>
#include "fileInfoStruct.h"
#include "databaseutils.h"

class InsertionThread : public QThread
{
    Q_OBJECT

public:
    InsertionThread();
    void setQueue(QQueue<FileInfo>* queue);
    void setStopAsked(bool stopAsked);
signals:
    void insertionAvailable(QQueue<FileInfo> *_queue);
    void finished();

protected:
    void run() override;
private:
    bool _stopAsked = false;
    QSqlDatabase* _db;
    QQueue<FileInfo>* _queue;
};

#endif // INSERTIONTHREAD_H
