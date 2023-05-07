#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QSpacerItem>
#include <QStandardItem>
#include <QDebug>
#include <QDir>
#include <QStorageInfo>
#include <QListWidgetItem>
#include <fileInfoStruct.h>
#include <MyThread.h>
#include <databaseutils.h>
#include <insertionthread.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    MyThread * _thread = nullptr;
    InsertionThread * _insertionThread= nullptr;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void updateProgressBar();
    void setDefaultParameters();
    QStringList getIndexationParameters();

private slots:
    void on_stopBtn_clicked();
    void on_startBtn_clicked();
    void on_btnSearch_clicked();
    void jobStarted();
    void jobFinished();
    void valueChanged(FileInfo fileInformation);
    void insertionAvailable(QQueue<FileInfo> *_queue);
private:
    Ui::MainWindow *ui;
    DatabaseUtils * _databaseUtils;
    QQueue<FileInfo> * _queue;
};
#endif // MAINWINDOW_H
