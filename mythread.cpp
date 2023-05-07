#include "mythread.h"

#include <QDir>
#include <QDirIterator>
#include <iostream>


void MyThread::setStopAsked(bool stopAsked)
{
    _stopAsked = stopAsked;
}
MyThread::MyThread()
{

}


void MyThread::run() {
    // Ouvrir le répertoire à partir du chemin spécifié
    QDir dir("C:/Users/sauri/OneDrive/Bureau/CodesProjets/asyncVsSync");

    QDirIterator it(dir.absolutePath(), QDirIterator::Subdirectories);
    int i = 0;
    while (it.hasNext()) {
        i++;
        if (_stopAsked)
            break;

        struct FileInfo actualFileInfo;

        QString file = it.next();
        QFileInfo fileInfo(file);
        actualFileInfo.name = fileInfo.fileName();
        actualFileInfo.path = fileInfo.filePath();
        actualFileInfo.created_at = fileInfo.birthTime();
        actualFileInfo.updated_at = fileInfo.lastModified();
        actualFileInfo.size = fileInfo.size();
        actualFileInfo.extension = fileInfo.completeSuffix();
        valueChanged(actualFileInfo);
    }
    _stopAsked = false;
}


