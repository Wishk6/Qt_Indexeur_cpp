#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), _thread(new MyThread),_insertionThread(new InsertionThread),
      ui(new Ui::MainWindow), _databaseUtils(new DatabaseUtils),
      _queue(new QQueue<FileInfo>)
{
    ui->setupUi(this);

    setDefaultParameters();

    _databaseUtils->setupDatabase();
    _databaseUtils->createTable();
    _insertionThread->setQueue(_queue); // Pass the queue to the insertion thread
    _databaseUtils->setQueue(_queue); // Pass the queue to the database utils

    connect(_thread, &MyThread::started, this, &MainWindow::jobStarted);
    connect(_thread, &MyThread::finished, this, &MainWindow::jobFinished);
    connect(_thread, &MyThread::valueChanged, this, &MainWindow::valueChanged);
    connect(_insertionThread, &InsertionThread::insertionAvailable, this, &MainWindow::insertionAvailable);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete _thread;
}


void MainWindow::setDefaultParameters() {

    QDir rootDir("/");
    QStringList topLevelFolders = rootDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    std::string extensions[] = {
        ".doc", ".docx", ".xls", ".xlsx", ".ppt", ".pptx", ".pdf", ".jpeg", ".jpg", ".png",
        ".gif", ".mp3", ".mp4", ".avi", ".mov", ".txt", ".html", ".htm", ".xml", ".zip",
        ".rar", ".exe", ".dll", ".bat", ".iso"};


    // Ajoute les extensions à la liste
    for (const auto& extension : extensions) {
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(extension));
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        ui->listWidget_2->addItem(item);
    }
    // Ajoute les folders à la liste
    for (const QString &folder : topLevelFolders) {
        QListWidgetItem *item = new QListWidgetItem(folder);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        ui->listWidget->addItem(item);
    }

}


QStringList MainWindow::getIndexationParameters() {


    QList<QString> selectedFolders; // Liste pour stocker les noms des dossiers sélectionnés

    for (int i = 0; i < ui->listWidget->count(); ++i) {
        QListWidgetItem* item = ui->listWidget->item(i);
        if (item->checkState() == Qt::Checked) {
            QString folderName = item->text(); // Récupérer le nom du dossier à partir de l'élément de la liste
            selectedFolders.append(folderName); // Ajouter le nom du dossier à la liste
        }
    }
    return selectedFolders;
}


void MainWindow::on_startBtn_clicked()
{
    //    _thread->start();
    //    _insertionThread->start();
    //    ui->progressBar->setRange(0, 0);
    //    ui->startBtn->setDisabled(true);
    //    ui->stopBtn->setDisabled(false);
    qDebug() << getIndexationParameters();
        // Faire quelque chose avec le chemin du dossier sélectionné

}

void MainWindow::jobStarted()
{

}

void MainWindow::on_stopBtn_clicked()
{
    _thread->setStopAsked(true);
    _insertionThread->setStopAsked(true);
    ui->startBtn->setDisabled(false);
    ui->stopBtn->setDisabled(true);
}

void MainWindow::jobFinished()
{
    _insertionThread->setStopAsked(true);
    ui->stopBtn->setDisabled(true);
    updateProgressBar();

}

void MainWindow::valueChanged(FileInfo fileInformation)
{
    _queue->enqueue(fileInformation);
}

void MainWindow::insertionAvailable(QQueue<FileInfo> *_queue) {

    _databaseUtils->insertDataFromQueue(_queue);
}

void MainWindow::updateProgressBar()
{
    ui->progressBar->setRange(0, 100);

    ui->progressBar->setValue(ui->progressBar->maximum());
}


void MainWindow::on_btnSearch_clicked()
{
    //    m_lexer->setPrompt(ui->linePrompt->text());
    //    m_lexer->compute();
    //    ui->animalOutput->setText(m_lexer->getAnimal());
    //    ui->determinantOutput->setText(m_lexer->getDeterminant());
    //    ui->pronounOutput->setText(m_lexer->getPronoun());
    //    ui->verbOutput->setText(m_lexer->getVerb());
}
