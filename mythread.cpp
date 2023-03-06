#include "mythread.h"

MyThread::MyThread(QObject *parent)
    : QThread{parent}
{

}

void MyThread::run() {
    int i =0;
    while (1) {
        i++;
        emit valueChanged();
        QThread::usleep(100); // delay pour pas que ca PETE

    }
}
