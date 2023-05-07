#include "insertionthread.h"
#include <QDebug>

InsertionThread::InsertionThread() {
}

void InsertionThread::run()
{
    while (true) {
        // attendre une seconde

        if (_stopAsked)
            break;

        sleep(2);
        // s'il y a des éléments dans la queue, les envoyer au signal pour insertion dans la base de données
        if (_queue->size() >= 100) {
            insertionAvailable(_queue);
        }
    }
}

void InsertionThread::setQueue(QQueue<FileInfo>* queue) {
    _queue = queue;
}

void InsertionThread::setStopAsked(bool stopAsked)
{
    _stopAsked = stopAsked;
}
