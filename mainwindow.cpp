#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), _thread(new MyThread)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(_thread, &MyThread::started, this, &MainWindow::jobStarted);
    connect(_thread, &MyThread::finished, this, &MainWindow::jobFinished);
     connect(_thread, &MyThread::valueChanged, this, &MainWindow::valueChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startBtn_clicked()
{
    _thread->start();
    ui->startBtn->setDisabled(true);
    ui->stopBtn->setDisabled(false);
}

void MainWindow::jobStarted()
{
    qDebug() << __FUNCTION__ << __LINE__;
}

void MainWindow::on_stopBtn_clicked()
{
    _thread->setStopAsked(true);
    ui->startBtn->setDisabled(false);
    ui->stopBtn->setDisabled(true);
}

void MainWindow::jobFinished()
{
    qDebug() << __FUNCTION__ << __LINE__;
}

void MainWindow::valueChanged(int val)
{
    qDebug() << __FUNCTION__ << __LINE__ << val;
    ui->valueLabel->setText(QString("The number of file scanned is %1").arg(val));
}

