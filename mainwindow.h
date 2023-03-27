#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <MyThread.h>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    MyThread * _thread = nullptr;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_stopBtn_clicked();

    void on_startBtn_clicked();
    void jobStarted();
    void jobFinished();
    void valueChanged(int i);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
