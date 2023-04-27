#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDir>
#include <QStorageInfo>
#include <QListWidgetItem>
#include <serverutils.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), _thread(new MyThread)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::string extensions[] = {
        ".doc", ".docx", ".xls", ".xlsx", ".ppt", ".pptx", ".pdf", ".jpeg", ".jpg", ".png",
        ".gif", ".mp3", ".mp4", ".avi", ".mov", ".txt", ".html", ".htm", ".xml", ".zip",
        ".rar", ".exe", ".dll", ".bat", ".iso"};

    for (const QString &folder : folderList) {
        QListWidgetItem *item = new QListWidgetItem(folder);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        ui->listWidget->addItem(item);
    }

    // Ajouter les extensions à la liste
    for (const auto& extension : extensions) {
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(extension));
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        ui->listWidget_2->addItem(item);
    }

    connect(_thread, &MyThread::started, this, &MainWindow::jobStarted);
    connect(_thread, &MyThread::finished, this, &MainWindow::jobFinished);
    connect(_thread, &MyThread::valueChanged, this, &MainWindow::valueChanged);

    QStringList folderList = setDefaultFolders();

}

MainWindow::~MainWindow()
{
    delete ui;
}


QStringList MainWindow::setDefaultFolders() {

    QDir rootDir("/");
    QStringList topLevelFolders = rootDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    return topLevelFolders;
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
    qDebug() << __FUNCTION__ << __TIMESTAMP__;
}

void MainWindow::valueChanged(QFileInfo fileInformation)
{ // voir pour le type QFileInfo
    // Start a transaction
    serverUtils.insertData(fileInformation);

    qDebug() << fileInformation.name;
}
