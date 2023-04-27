#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QDateTime>

struct FileInfo {
   QString name;
   QString path;
   QDateTime created_at;
   QDateTime updated_at;
   qint64 size;
   QString extension;
};

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
