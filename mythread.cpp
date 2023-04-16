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
    QDir dir("C:/Users/sauri/OneDrive/Bureau/G");

    QDirIterator it(dir.absolutePath(), QDirIterator::Subdirectories);
    int i = 0;
    while (it.hasNext()) {
        i++;
        valueChanged(i);
//        if (_pauseAsked)
//            pause;
        if (_stopAsked)
            break;
        QString file = it.next();
        QFileInfo fileInfo(file);
        QString fileName = fileInfo.fileName();
             QString filePath = fileInfo.filePath();
             QDateTime fileCreated = fileInfo.birthTime();
             QDateTime fileModified = fileInfo.lastModified();
             qint64 fileSize = fileInfo.size();
             QString fileExtension = fileInfo.completeSuffix();

             // Utiliser les informations extraites comme nécessaire
             qDebug() << "File found: " << fileName;
             qDebug() << "File path: " << filePath;
             qDebug() << "File created: " << fileCreated.toString();
             qDebug() << "File modified: " << fileModified.toString();
             qDebug() << "File size: " << fileSize << " bytes";
             qDebug() << "File extension: " << fileExtension;
        QThread::usleep(1);
    }
    qDebug() << it.hasNext() << "test";
                // Réinitialiser la variable d'arrêt du thread
                _stopAsked = false;
}


