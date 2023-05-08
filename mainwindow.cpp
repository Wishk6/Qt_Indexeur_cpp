#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), _thread(new LectureThread),_insertionThread(new InsertionThread)/*,_searchLexer(new SearchLexer)*/,
      ui(new Ui::MainWindow), _databaseUtils(new DatabaseUtils),
      _queue(new QQueue<FileInfo>)
{
    ui->setupUi(this);
    ui->indexationTabWidget->setTabText(0,"Interface d'indexation");
    ui->indexationTabWidget->setTabText(1,"Interface de recherche");
    ui->progressBar->setVisible(false);

    // TODO:  enlever tous les setup une fois que l'indexation passera par le lexer
    setDefaultParameters();
    _databaseUtils->setupDatabase();
    _databaseUtils->createTable();

    ui->dbCount->setText(QString::number(_databaseUtils->countItems()));

    connect(_thread, &LectureThread::started, this, &MainWindow::jobStarted);
    connect(_thread, &LectureThread::finished, this, &MainWindow::jobFinished);
    connect(_thread, &LectureThread::valueChanged, this, &MainWindow::valueChanged);
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
        "doc", "docx", "xls", "xlsx", "ppt", "pptx", "pdf", "jpeg", "jpg", "png",
        "gif", "mp3", "mp4", "avi", "mov", "txt", "html", "htm", "xml", "zip",
        "rar", "exe", "dll", "bat", "iso"};

    // Ajoute les extensions à la liste
    for (const auto& extension : extensions) {
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(extension));
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        ui->listWidget_2->addItem(item);
    }
    // Ajoute les folders à la liste
    for (const QString &folder : topLevelFolders) {
        QListWidgetItem *item =new QListWidgetItem(rootDir.absolutePath() + folder);;
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        ui->listWidget->addItem(item);
    }

}

QStringList MainWindow::getIndexationParameters(QListWidget *_myListWidget)
{
    QStringList selectedItemsList; // Liste pour stocker les noms des dossiers sélectionnés

    for (int i = 0; i < _myListWidget->count(); ++i) {
        QListWidgetItem* item = _myListWidget->item(i);
        if (item->checkState() == Qt::Checked) {
            QString extensionName = item->text(); // Récupérer le nom du dossier à partir de l'élément de la liste
            selectedItemsList.append(extensionName); // Ajouter le nom du dossier à la liste
        }
    }
    return selectedItemsList;
}


void MainWindow::on_startBtn_clicked()
{
    _thread->setSelectedFolders(getIndexationParameters(ui->listWidget));
    _thread->setSelectedExtensions(getIndexationParameters(ui->listWidget_2));
    _thread->start();

    _insertionThread->start();
    ui->progressBar->setVisible(true);
    ui->progressBar->setRange(0, 0);
    ui->startBtn->setDisabled(true);
    ui->stopBtn->setDisabled(false);
}

void MainWindow::jobStarted()
{
    _insertionThread->setQueue(_queue); // Pass the queue to the insertion thread
    _databaseUtils->setQueue(_queue); // Pass the queue to the database utils
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
    ui->startBtn->setDisabled(false);
    updateProgressBar();
    ui->dbCount->setText(QString::number(_databaseUtils->countItems()));
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

void MainWindow::on_pushButton_clicked()
{
    //    QStringList input = ui->searchInput->text().split(" ");
    //    QString result = _searchLexer->Tokenize(input, _databaseUtils);
    //    qDebug(result);
}

//void MainWindow::on_SearchWindowBtn_clicked()
//{

//    //    m_lexer->setPrompt(ui->linePrompt->text());
//    //    m_lexer->compute();
//        // set dans l'ui après recherche
//}




