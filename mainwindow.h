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
#include <LectureThread.h>
#include <databaseutils.h>
#include <insertionthread.h>
#include <searchlexer.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    LectureThread * _thread = nullptr;
    InsertionThread * _insertionThread= nullptr;
    SearchLexer * _searchLexer;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void updateProgressBar();
    void setDefaultParameters();
    QStringList getIndexationParameters(QListWidget * _myListWidget);
private slots:
    void on_stopBtn_clicked();
    void on_startBtn_clicked();
    void jobStarted();
    void jobFinished();
    void valueChanged(FileInfo fileInformation);
    void insertionAvailable(QQueue<FileInfo> *_queue);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    DatabaseUtils * _databaseUtils;
    QQueue<FileInfo> * _queue;
};
#endif // MAINWINDOW_H
