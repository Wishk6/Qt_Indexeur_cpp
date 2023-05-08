#include "lecturethread.h"

#include <QDir>
#include <QDirIterator>
#include <iostream>


void LectureThread::setStopAsked(bool stopAsked)
{
    _stopAsked = stopAsked;
}

LectureThread::LectureThread(QStringList folderNames, QStringList extensions)
    : _selectedFolders(folderNames), _selectedExtensions(extensions)
{
}

void LectureThread::run() {
    // Parcourir les dossiers sélectionnés

    for (QString folderPath : _selectedFolders) {
        QDir dir(folderPath);
        QDirIterator it(dir.absolutePath(), QDirIterator::Subdirectories | QDirIterator::NoIteratorFlags);
        // Parcourir les fichiers du dossier courant
        while (it.hasNext()) {
            if (_stopAsked)
                break;

            QString filePath = it.next();
            QFileInfo fileInfo(filePath);

            if (_selectedExtensions.contains(fileInfo.completeSuffix())) {
                struct FileInfo actualFileInfo;
                actualFileInfo.name = fileInfo.fileName();
                actualFileInfo.path = fileInfo.filePath();
                actualFileInfo.created_at = fileInfo.birthTime();
                actualFileInfo.updated_at = fileInfo.lastModified();
                actualFileInfo.size = fileInfo.size();
                actualFileInfo.extension = fileInfo.completeSuffix();

                // Émettre le signal pour envoyer les informations du fichier
                valueChanged(actualFileInfo);
            }
        }
    }
    _stopAsked = false;
}

void LectureThread::setSelectedFolders(QStringList foldersList) {
    _selectedFolders = foldersList;
}


void LectureThread::setSelectedExtensions(QStringList extensionsList) {
    _selectedExtensions = extensionsList;
}
