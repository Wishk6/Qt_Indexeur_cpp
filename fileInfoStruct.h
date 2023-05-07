#ifndef FILEINFOSTRUCT_H
#define FILEINFOSTRUCT_H
#include <QString>
#include <QDateTime>

struct FileInfo {
   QString name;
   QString path;
   QDateTime created_at;
   QDateTime updated_at;
   qint64 size;
   QString extension;
};

#endif // FILEINFOSTRUCT_H
