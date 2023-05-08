//#include <searchlexer.h>


//SearchLexer::SearchLexer() {
//    _dialectMap["query"] = {"SEARCH"};
//    _dialectMap["options"] = {"LAST_MODIFIED","CREATED","MAX_SIZE","MIN_SIZE","SIZE","EXT"};
//}


//QStringList SearchLexer::Tokenize(QStringList input, DatabaseUtils dbUtils)
//{
//    setFileName(input);
//    QString sqlQuery = "SELECT * FROM files WHERE filename LIKE :file";
//    QStringList options;
//    for(int i=1; i<input.size(); i++){
//        QString token = input[i];
//        if(_dialectMap["options"].contains(token)){
//            if(token == "EXT"){
//                QString extension = input[i+1];
//                sqlQuery += " AND filename LIKE '%" + extension + "'";
//                options.append("EXT:" + extension);
//                i++;
//            }
//            else if(token == "LAST_MODIFIED"){
//                QDateTime lastModified = QDateTime::fromString(input[i+1], Qt::ISODate);
//                sqlQuery += " AND last_modified >= '" + lastModified.toString(Qt::ISODate) + "'";
//                options.append("LAST_MODIFIED:" + lastModified.toString(Qt::ISODate));
//                i++;
//            }
//            else if(token == "CREATED"){
//                QDateTime created = QDateTime::fromString(input[i+1], Qt::ISODate);
//                sqlQuery += " AND created_at >= '" + created.toString(Qt::ISODate) + "'";
//                options.append("CREATED:" + created.toString(Qt::ISODate));
//                i++;
//            }
//            else if(token == "SIZE"){
//                qint64 size = input[i+1].toLongLong();
//                sqlQuery += " AND size == " + QString::number(size);
//                options.append("SIZE:" + QString::number(size));
//                i++;
//            }
//            else if(token == "MAX_SIZE"){
//                qint64 maxSize = input[i+1].toLongLong();
//                sqlQuery += " AND size <= " + QString::number(maxSize);
//                options.append("MAX_SIZE:" + QString::number(maxSize));
//                i++;
//            }
//            else if(token == "MIN_SIZE"){
//                qint64 minSize = input[i+1].toLongLong();
//                sqlQuery += " AND size >= " + QString::number(minSize);
//                options.append("MIN_SIZE:" + QString::number(minSize));
//                i++;
//            }
//        }
//    }

//    if(options.isEmpty()){
//        options.append("ALL");
//    }

//    return getQueryResult(sqlQuery, dbUtils);
//}


//bool SearchLexer::isSearch(QStringList input)
//{
//    return _dialectMap["query"].contains(input.first());
//}

//bool SearchLexer::isOption(QStringList input)
//{
//    for(QString token : input){
//        if(_dialectMap["options"].contains(token))
//            return true;

//    }
//    return false;
//}

//QStringList SearchLexer::getQueryResult(QString sqlQuery, DatabaseUtils dbUtils)
//{
//    return dbUtils.getDataWithParams(sqlQuery,getFileName());
//}

//void SearchLexer::setFileName(const QStringList& input)
//{
//    QString filename;
//    for (const QString& token : input) {
//        if (_dialectMap["options"].contains(token)) {
//            break;
//        }
//        filename += token + " ";
//    }
//    filename = filename.trimmed();
//    fileName = "%" + filename + "%";
//    qDebug() << "Nom du fichier : " << filename;
//}

//QString SearchLexer::getFileName()
//{
//    return fileName;
//}
