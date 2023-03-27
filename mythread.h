#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
    bool _stopAsked = false;
public:
    MyThread();
    void run() override;
    void setStopAsked(bool stopAsked);
signals:
    void valueChanged(int i);
};

#endif // MYTHREAD_H
