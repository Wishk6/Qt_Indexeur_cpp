#ifndef LECTURETHREAD_H
#define LECTURETHREAD_H

#include <QThread>
#include <QDateTime>
#include "fileInfoStruct.h"

class LectureThread : public QThread
{
    Q_OBJECT
public:
    LectureThread(QObject* parent = nullptr) : QThread(parent) {}
    LectureThread(QStringList folderNames, QStringList extensions);
    void setStopAsked(bool stopAsked);
    void setSelectedFolders(QStringList foldersList);
    void setSelectedExtensions(QStringList extensionsList);
signals:
    void valueChanged(FileInfo fileInformation);
protected:
    void run() override;
private:
    QStringList _selectedFolders; // liste des dossiers
    QStringList _selectedExtensions; // liste des extensions
    bool _stopAsked;
};

#endif // LECTURETHREAD_H
