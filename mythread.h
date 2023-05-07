#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QDateTime>
#include "fileInfoStruct.h"

class MyThread : public QThread
{
    Q_OBJECT
    bool _stopAsked = false;
public:
    MyThread();
    void run() override;
    void setStopAsked(bool stopAsked);
signals:
    void valueChanged(FileInfo fileInformation);
};

#endif // MYTHREAD_H
