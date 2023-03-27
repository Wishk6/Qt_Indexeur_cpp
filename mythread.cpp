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
    QDir dir("C:/Users/sauri");

    QDirIterator it(dir.absolutePath(), QDirIterator::Subdirectories);
       int i = 0;
    while (it.hasNext()) {
        i++;
        valueChanged(i);
        if (_stopAsked)
                  break;
        QString file = it.next();
        qDebug() << "File found: " << file;
             QThread::usleep(300);
    }
    // Réinitialiser la variable d'arrêt du thread
    _stopAsked = false;
}


