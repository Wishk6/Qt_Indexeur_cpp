#include <QApplication>
#include <QPushButton>
#include <QDirIterator>
#include <QThread>

void indexFiles() {
    // Créer un QDirIterator pour parcourir tous les fichiers du système
    QDirIterator it(QDir::rootPath(), QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);

    // Boucler sur tous les fichiers trouvés
    while (it.hasNext()) {
        QString file = it.next();
        // Faire quelque chose avec le fichier, par exemple l'afficher dans la console
        qDebug() << file;
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Créer un bouton pour démarrer l'indexation des fichiers
    QPushButton button("Index Files");

    // Créer un thread pour exécuter l'indexation
    QThread thread;

    // Connecter le signal "clicked()" du bouton au slot "start()" du thread
    QObject::connect(&button, &QPushButton::clicked, &thread, &QThread::start);

    // Lorsque le thread est démarré, exécuter la fonction d'indexation
    QObject::connect(&thread, &QThread::started, indexFiles);

    // Afficher le bouton
    button.show();

    return app.exec();
}
